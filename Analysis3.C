#include <TFile.h>
#include <TTree.h>
#include <TSystem.h>

#include <iostream>
#include <map>
#include <tuple>
#include <cmath>

#include "include/Observation.h"

#include <TGraphErrors.h>
#include <TCanvas.h>
#include <TAxis.h>

void Analysis3() {

    if (gSystem->Load("./libObservation.so") < 0) {
        std::cerr << "Error: could not load libObservation.so" << std::endl;
        return;
    }

    TFile *inputFile = TFile::Open("temperature_tree.root", "READ");

    if (!inputFile || inputFile->IsZombie()) {
        std::cerr << "Error: could not open temperature_tree.root" << std::endl;
        return;
    }

    TTree *tree = nullptr;
    inputFile->GetObject("measurements", tree);

    if (!tree) {
        std::cerr << "Error: measurements tree not found" << std::endl;
        inputFile->Close();
        return;
    }

    Observation *measurement = nullptr;
    tree->SetBranchAddress("measurements", &measurement);

    // Sum and count of measurements for each actual date.
    std::map<std::tuple<int, int, int>, std::pair<double, int>> dailyData;

    Long64_t entries = tree->GetEntries();

    for (Long64_t i = 0; i < entries; ++i) {
        tree->GetEntry(i);

        if (!measurement) continue;

        int year = measurement->Year();
        int month = measurement->Month();
        int day = measurement->Day();
        double temperature = measurement->Temperature();

        // Exclude February 29.
        if (month == 2 && day == 29) continue;

        auto date = std::make_tuple(year, month, day);
        dailyData[date].first += temperature;
        dailyData[date].second++;
    }

    // Statistics for each day of a common 365-day calendar.
    double sumTemperature[366] = {};
    double sumSquaredTemperature[366] = {};
    int numberOfDates[366] = {};

    const int daysInMonth[12] =
        {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    for (const auto &entry : dailyData) {

        int year = std::get<0>(entry.first);
        int month = std::get<1>(entry.first);
        int day = std::get<2>(entry.first);

        double dailyMean =
            entry.second.first / entry.second.second;

        int dayOfYear = day;

        for (int m = 1; m < month; ++m) {
        dayOfYear += daysInMonth[m - 1];
        }

        sumTemperature[dayOfYear] += dailyMean;
        sumSquaredTemperature[dayOfYear] += dailyMean * dailyMean;
        numberOfDates[dayOfYear]++;

    }

    // Create the output ROOT file.
    TFile *outputFile = TFile::Open("Analysis3.root", "RECREATE");

    if (!outputFile || outputFile->IsZombie()) {
        std::cerr << "Error: could not create Analysis3.root" << std::endl;
        tree->ResetBranchAddresses();
        inputFile->Close();
        return;
    }

    TTree *results = new TTree(
        "daily_statistics",
        "Temperature statistics for each day of the year"
    );

    int dayOfYear = 0;
    int nDates = 0;
    double meanTemperature = 0.0;
    double standardDeviation = 0.0;

    results->Branch("dayOfYear", &dayOfYear, "dayOfYear/I");
    results->Branch("meanTemperature", &meanTemperature, "meanTemperature/D");
    results->Branch("standardDeviation", &standardDeviation, "standardDeviation/D");
    results->Branch("numberOfDates", &nDates, "numberOfDates/I");

    std::cout << "Day\tMean (C)\tStd. dev. (C)\tNumber of dates"
              << std::endl;

    for (dayOfYear = 1; dayOfYear <= 365; ++dayOfYear) {

        nDates = numberOfDates[dayOfYear];

        if (nDates > 0) {
            meanTemperature = sumTemperature[dayOfYear] / nDates;

            double variance =
                sumSquaredTemperature[dayOfYear] / nDates
                - meanTemperature * meanTemperature;

            if (variance < 0.0) variance = 0.0;

            standardDeviation = std::sqrt(variance);
        } else {
            meanTemperature = 0.0;
            standardDeviation = 0.0;
        }

        results->Fill();

        std::cout << dayOfYear << "\t"
                  << meanTemperature << "\t\t"
                  << standardDeviation << "\t\t"
                  << nDates << std::endl;
    }

    results->Write();
    outputFile->Close();

    tree->ResetBranchAddresses();
    inputFile->Close();

    std::cout << "\nSaved results to Analysis3.root" << std::endl;

        // Create the temperature graph.
    TGraphErrors *graph = new TGraphErrors();

    for (int day = 1; day <= 365; ++day) {
        int n = numberOfDates[day];

        if (n == 0) continue;

        double mean = sumTemperature[day] / n;

        double variance =
            sumSquaredTemperature[day] / n - mean * mean;

        if (variance < 0.0) variance = 0.0;

        double standardDeviation = std::sqrt(variance);

        int point = graph->GetN();

        graph->SetPoint(point, day, mean);
        graph->SetPointError(point, 0.0, standardDeviation);
    }

    TCanvas *canvas = new TCanvas(
        "canvas", "Temperature by day of year", 1000, 600
    );

    graph->SetTitle(
        "Mean Temperature for Each Day of the Year;"
        "Day of Year;"
        "Mean Temperature (#circC)"
    );

    graph->SetMarkerStyle(20);
    graph->SetMarkerSize(0.5);
    graph->SetLineWidth(2);

    graph->Draw("AP");
    graph->GetXaxis()->SetLimits(1, 365);
    graph->GetXaxis()->SetNdivisions(12);

    canvas->SaveAs("Analysis3.pdf");
}