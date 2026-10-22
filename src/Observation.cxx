#include "Observation.h"

// Constructor with parameters definition
Observation::Observation(Int_t year, Int_t month, Int_t day, Int_t hour, Double_t temperature) : 
    _year{year}, _month{month}, _day{day}, _hour{hour}, _temperature{temperature} {}

// Getters definition
Int_t Observation::Year() const { return _year; }

Int_t Observation::Month() const { return _month; }

Int_t Observation::Day() const { return _day; }

Int_t Observation::Hour() const { return _hour; }

Double_t Observation::Temperature() const { return _temperature; }

// Setter definition
void Observation::SetObservation(Int_t year, Int_t month, Int_t day, Int_t hour, Double_t temperature) {

    _year = year;
    _month = month;
    _day = day;
    _hour = hour;
    _temperature = temperature;

}



