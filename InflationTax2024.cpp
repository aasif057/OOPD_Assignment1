// InflationTax2024.cpp
#include "InflationTax2024.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>

InflationTax2024::InflationTax2024(double price, int purchaseYear)
    : initialPrice(price), yearOfPurchase(purchaseYear), yearOfSale(0) {}

void InflationTax2024::loadRatesFromCSV(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file.");
    }
    std::string line;
    std::getline(file, line); // Skip header
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string date, growthPriceStr;

        if (std::getline(ss, date, ',') && std::getline(ss, growthPriceStr, ',')) {
            int year = std::stoi(date.substr(0, 4));
            double growthPrice = std::stod(growthPriceStr);

            propertyRateIncreases[year] = growthPrice;
        }
    }
    file.close();
}

void InflationTax2024::setYearOfSale(int year) {
    if (propertyRateIncreases.empty()) {
        throw std::runtime_error("Property rate data is empty. Please check the CSV file.");
    }

    int lastYear = (--propertyRateIncreases.end())->first;

    if (year < yearOfPurchase || year > lastYear) {
        std::cerr << "Error: Invalid year of sale. Valid years are between " 
                  << yearOfPurchase << " and " << lastYear << "." << std::endl;
        throw std::invalid_argument("Invalid year of sale.");
    }
    yearOfSale = year;
}

double InflationTax2024::calculateSellingPrice() const {
    double price = initialPrice;
    for (int year = yearOfPurchase + 1; year <= yearOfSale; ++year) {
        price *= (1 + propertyRateIncreases.at(year) / 100.0);
    }
    return price;
}

double InflationTax2024::calculateLTCG() const {
    double adjustedProfit = calculateSellingPrice() - initialPrice;
    return adjustedProfit * 0.125; // 12.5% LTCG tax rate
}

