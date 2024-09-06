#include <iostream>
#include "InflationTax.hpp"
#include "InflationTax2024.hpp"

using namespace std;

int main() {
    double initialPrice = 5000000.0; // 50 lakhs
    int yearOfPurchase = 2010;
    int yearOfSale;
    
    cout << "Initial Purchase Price: 50 lakhs" << endl;
    cout << "Year of Purchase: 2010" << endl;
    cout << "Enter the year of sale: ";
    cin >> yearOfSale;

    // Old LTCG Scheme
    InflationTax oldTaxCalculator(initialPrice, yearOfPurchase);
    try {
        oldTaxCalculator.loadRatesFromCSV("price-inflation.csv");
        oldTaxCalculator.setYearOfSale(yearOfSale);

        double oldSellingPrice = oldTaxCalculator.calculateSellingPrice();
        oldSellingPrice /= 100000.0; // Convert to lakhs
        double oldLTCG = oldTaxCalculator.calculateLTCG();

        cout << "Old Scheme - Estimated Selling Price: Rs " << fixed << setprecision(2) << oldSellingPrice << " lakhs" << endl;
        cout << "Old Scheme - LTCG Tax to be paid: Rs " << oldLTCG << endl;
    }
    catch (const exception& e) {
        cerr << e.what() << endl;
    }

    // New LTCG Scheme
    InflationTax2024 newTaxCalculator(initialPrice, yearOfPurchase);
    try {
        newTaxCalculator.loadRatesFromCSV("price-inflation.csv");
        newTaxCalculator.setYearOfSale(yearOfSale);

        double newSellingPrice = newTaxCalculator.calculateSellingPrice();
        newSellingPrice /= 100000.0; // Convert to lakhs
        double newLTCG = newTaxCalculator.calculateLTCG();

        cout << "New Scheme - Estimated Selling Price: Rs " << fixed << setprecision(2) << newSellingPrice << " lakhs" << endl;
        cout << "New Scheme - LTCG Tax to be paid: Rs " << newLTCG << endl;

        // Compare the taxes
        double taxDifference = oldLTCG - newLTCG;
        cout << "Difference in LTCG Tax between Old and New Schemes: Rs " << taxDifference << endl;
    }
    catch (const exception& e) {
        cerr << e.what() << endl;
    }

    return 0;
}

