void Analysis2()
{
    TFile *file = new TFile("Analysis2.root");
    TTree *tree = (TTree*)file->Get("analysis2");

    TCanvas *c1 = new TCanvas("c1", "Analysis 2", 800, 600);

    c1->SetGrid();

    tree->SetMarkerStyle(20);
    tree->SetMarkerSize(0.8);
    tree->SetMarkerColor(kBlue);

    tree->Draw("warm_days:year", "", "P");

    tree->GetHistogram()->SetTitle("Summer days >= 25 C in Lund");
    tree->GetHistogram()->GetXaxis()->SetTitle("Year");
    tree->GetHistogram()->GetYaxis()->SetTitle("Number of days (June-August)");
    c1->SaveAs("Analysis2.pdf");
}
