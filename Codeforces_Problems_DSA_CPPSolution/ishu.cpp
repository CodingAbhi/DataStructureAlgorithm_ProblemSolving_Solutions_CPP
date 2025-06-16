#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath> // for floor function

using namespace std;

// Function to calculate the discounted price of an item
int discountedPrice(int price, int coupons) {
    while (coupons--) {
        price = floor(price / 2.0);
    }
    return price;
}

// Function to find the minimum amount required with optimization of coupons
int findMinimumPrice(vector<int>& price, int m) {
    int n = price.size();
    vector<int> costs(n);
    vector<pair<int, int>> savings(n); // (savings, index)

    // Calculate costs without any discount and potential savings
    for (int i = 0; i < n; i++) {
        costs[i] = price[i]; // initial cost without discount
        int discounted = discountedPrice(price[i], m);
        savings[i] = {price[i] - discounted, i}; // calculate potential maximum savings
    }

    // Sort the potential savings in descending order
    sort(savings.rbegin(), savings.rend());

    // Apply the discounts to the items with the most potential savings
    int totalCost = 0, couponsUsed = 0;
    vector<int> discountsApplied(n, 0);
    for (int i = 0; i < n && couponsUsed < m; i++) {
        int idx = savings[i].second;
        int maxCoupons = min(m - couponsUsed, m); // maximum coupons that can be used for this item
        discountsApplied[idx] = maxCoupons;
        couponsUsed += maxCoupons;
    }

    // Recalculate costs with optimal coupon distribution
    for (int i = 0; i < n; i++) {
        totalCost += discountedPrice(price[i], discountsApplied[i]);
    }

    return totalCost;
}

int main() {
    vector<int> prices = {2, 41}; // Item prices
    int m = 2; // Number of coupons available

    int minCost = findMinimumPrice(prices, m);
    cout << "Minimum total cost: " << minCost << endl;

    return 0;
}
