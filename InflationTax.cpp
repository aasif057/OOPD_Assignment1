#include "InflationTax.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>    
using namespace std;

InflationTax::InflationTax(double price, int purchaseYear)
    : initialPrice(price), yearOfPurchase(purchaseYear), yearOfSale(0) {}

void InflationTax::loadRatesFromCSV(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Could not open file.");
    }
    string line;
    getline(file,line);
    while (getline(file, line)) {
        stringstream ss(line);
        string date, growthPriceStr, inflationRateStr;

        // Read each field from the CSV
        if (getline(ss, date, ',') && getline(ss, growthPriceStr, ',') && getline(ss, inflationRateStr, ',')) {
            // Extract year from the date
            int year = stoi(date.substr(0, 4));
            double growthPrice = stod(growthPriceStr);
            double inflationRate = stod(inflationRateStr);

            // Debug output to check values
            // cout << "Year: " << year << ", Growth-Price: " << growthPrice << ", Inflation: " << inflationRate << endl;

            inflationRates[year] = inflationRate;
            propertyRateIncreases[year] = growthPrice;
        }
    }
    file.close();
}

void InflationTax::setYearOfSale(int year) {
    if (propertyRateIncreases.empty()) {
        throw runtime_error("Property rate data is empty. Please check the CSV file.");
    }

    int lastYear = (--propertyRateIncreases.end())->first; // Get the last available year in the map

    if (year < yearOfPurchase || year > lastYear) {
        cerr << "Error: Invalid year of sale. Valid years are between " 
                  << yearOfPurchase << " and " << lastYear << "." << endl;
        throw invalid_argument("Invalid year of sale.");
    }
    yearOfSale = year;
}

double InflationTax::calculateSellingPrice() const {
    double price = initialPrice;
    for (int year = yearOfPurchase + 1; year <= yearOfSale; ++year) {
        price *= (1 + propertyRateIncreases.at(year) / 100.0);
    }
    return price;
}

double InflationTax::calculateAdjustedProfit() const {
    double sellingPrice = calculateSellingPrice();
    double adjustedProfit = sellingPrice - initialPrice;
    for (int year = yearOfPurchase + 1; year <= yearOfSale; ++year) {
        adjustedProfit /= (1 + inflationRates.at(year) / 100.0);
    }
    return adjustedProfit;
}

double InflationTax::calculateLTCG() const {
    double adjustedProfit = calculateAdjustedProfit();
    return adjustedProfit * 0.20; // 20% LTCG tax rate
}

