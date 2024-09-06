#include "InflationTax.hpp"
#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    double initialPrice = 5000000.0; // 50 lakhs
    int yearOfPurchase = 2010;
    int yearOfSale;
    cout << "Initial Purchase Price: 50 lakhs" << endl;
    cout << "Year of Purchase: 2010" << endl;
    cout << "Enter the year of sale: ";
    cin >> yearOfSale;

    InflationTax taxCalculator(initialPrice, yearOfPurchase);
    
    try {
        taxCalculator.loadRatesFromCSV("price-inflation.csv");
        taxCalculator.setYearOfSale(yearOfSale);

        double sellingPrice = taxCalculator.calculateSellingPrice();
        sellingPrice = sellingPrice/100000.0;
        double ltcg = taxCalculator.calculateLTCG();

        cout << "Estimated Selling Price: Rs " << fixed << setprecision(2) << sellingPrice << " lakhs" << endl;
        cout << "LTCG Tax to be paid: Rs " << ltcg << endl;

    } catch (const exception& e) {
        cerr << e.what() << endl;
    }

    return 0;
}

