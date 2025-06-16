#include <bits/stdc++.h>
using namespace std;

int minFerryTrips(vector<int> passengerWeights, int limit) {
    sort(passengerWeights.begin(), passengerWeights.end());
    
    int trips = 0;
    int i = 0;
    int j = passengerWeights.size() - 1; 
    
    while (i <= j) {
      
        if (passengerWeights[i] + passengerWeights[j] <= limit) {
            i++; 
        }
        j--;
        trips++;
    }

    return trips;
}

int main() {
    int n, limit;
    cout << "Enter the number of passengers: ";
    cin >> n;
    
    vector<int> weights(n);
    cout << "Enter the weights of passengers:\n";
    for (int i = 0; i < n; i++) {
        cin >> weights[i];
    }
    
    cout << "Enter the weight limit of the ferry: ";
    cin >> limit;
    
    cout << "Minimum number of trips required: " << minFerryTrips(weights, limit) << endl;
    return 0;
}
