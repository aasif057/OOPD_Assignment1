// InflationTax2024.hpp
#ifndef INFLATION_TAX_2024_HPP
#define INFLATION_TAX_2024_HPP

#include <iostream>
#include <map>
#include <string>

class InflationTax2024 {
private:
    double initialPrice;
    int yearOfPurchase;
    int yearOfSale;
    std::map<int, double> propertyRateIncreases;

public:
    InflationTax2024(double price, int purchaseYear);
    void loadRatesFromCSV(const std::string& filename);
    void setYearOfSale(int year);
    double calculateSellingPrice() const;
    double calculateLTCG() const;
};

#endif // INFLATION_TAX_2024_HPP

