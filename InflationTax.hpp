#ifndef INFLATION_TAX_HPP
#define INFLATION_TAX_HPP
using namespace std;
#include <iostream>
#include <map>
#include <string>

class InflationTax {
private:
    double initialPrice;
    int yearOfPurchase;
    int yearOfSale;
    map<int, double> inflationRates;
    map<int, double> propertyRateIncreases;

public:
    InflationTax(double price, int purchaseYear);
    void loadRatesFromCSV(const string& filename);
    void setYearOfSale(int year);
    double calculateSellingPrice() const;
    double calculateAdjustedProfit() const;
    double calculateLTCG() const;
};

#endif // INFLATION_TAX_HPP
