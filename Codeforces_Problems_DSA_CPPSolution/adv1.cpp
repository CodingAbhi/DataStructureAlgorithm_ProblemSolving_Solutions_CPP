#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

int getMaximumPower(vector<int>& arr, vector<int>& power) {
    int n = arr.size();
    int k = power.size();
    long long maxPower = 0;

    for (int op = 0; op < k / 2; op++) {
        int maxSum = 0;
        int bestI = -1, bestJ = -1;

        // Find the subarray with maximum sum
        for (int i = 0; i < n; i++) {
            int sum = 0;
            for (int j = i; j < n; j++) {
                sum += arr[j];
                if (sum > maxSum) {
                    maxSum = sum;
                    bestI = i;
                    bestJ = j;
                }
            }
        }

        if (bestI != -1 && bestJ != -1) {
            // Choose the higher power between bestI and bestJ
            int selectedPower = max(power[bestI], power[bestJ]);
            maxPower += (long long)maxSum * selectedPower;

            // Remove used elements
            arr.erase(arr.begin() + bestI, arr.begin() + bestJ + 1);
            power.erase(power.begin() + bestJ);
            power.erase(power.begin() + bestI);
            n = arr.size();
        }
    }

    return maxPower % MOD;
}

int main() {
    vector<int> arr = {3, 5, 6, 0, 7};
    vector<int> power = {3, 1, 0, 2};
    cout << getMaximumPower(arr, power) << endl;
    return 0;
}