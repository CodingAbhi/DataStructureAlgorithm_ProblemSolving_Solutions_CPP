#include <bits/stdc++.h>
using namespace std;

int getMaxBarrier(vector<int> initialEnergy, int th) {
    int low = 0, high = *max_element(initialEnergy.begin(), initialEnergy.end());
    int bestBarrier = 0;

    while (low <= high) {
        int mid = (low + high) / 2;
        int sum = 0;
        
        for (int energy : initialEnergy) {
            sum += max(energy - mid, 0);
        }
        
        if (sum >= th) {
            bestBarrier = mid; // This barrier satisfies the condition
            low = mid + 1;     // Try for a higher barrier
        } else {
            high = mid - 1;    // Try for a lower barrier
        }
    }
    
    return bestBarrier;
}

int main() {
    vector<int> initialEnergy = {4, 8, 7, 1, 2};
    int th = 9;
    cout << "Maximum barrier: " << getMaxBarrier(initialEnergy, th) << endl;
    return 0;
}
