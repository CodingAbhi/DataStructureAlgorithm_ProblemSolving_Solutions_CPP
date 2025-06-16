#include <bits/stdc++.h>
#include <vector>
#include <unordered_set>
#include <cmath>

using namespace std;

int specialSum(int n, vector<int>& nums) {
    // Use a set to collect unique elements
    set<int> unique_set(nums.begin(), nums.end());

    // Transfer unique elements to a vector
    vector<int> unique_nums(unique_set.begin(), unique_set.end());
   

    // Calculate the special sum
    int special_sum = 0;
    for (int i = 0; i < unique_nums.size(); ++i) {
        // special_sum += pow(2, i + 1) * unique_nums[i] * unique_nums[i]; // taking squares of unique elements
        special_sum += pow(2, unique_nums[i]);
    }

    return special_sum;
}

int main() {
    int n;
    cin >> n;
    vector<int> nums(n);
    for (int i = 0; i < n; ++i) {
        cin >> nums[i];
    }

    cout << specialSum(n, nums) << endl;

    return 0;
}
