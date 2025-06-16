#include <iostream>
#include <vector>

using namespace std;

int maxCost(vector<int> &arr, vector<int> &cost, int k)
{
    int n = arr.size();
    int max_sum = 0;

    // Initialize a memoization table to store the maximum cost for a given subproblem
    vector<vector<int>> dp(k + 1, vector<int>(n, 0));

    // Fill in the dp table using dynamic programming
    for (int i = 1; i <= k; i++)
    {
        for (int j = 0; j < n; j++)
        {
            // Calculate the maximum cost if we remove the first element
            int remove_first = dp[i - 1][j + 1] + cost[j] * arr[j];

            // Calculate the maximum cost if we remove the last element
            int remove_last = dp[i - 1][j] + cost[j] * arr[n - 1 - j];

            // Choose the maximum cost between removing the first and last element
            dp[i][j] = max(remove_first, remove_last);
        }
    }

    // The maximum cost after performing k operations will be stored in dp[k][0]
    max_sum = dp[k][0];

    return max_sum;
}

int main()
{
    int n, k;
    cout << "Enter the number of elements in the array: ";
    cin >> n;

    vector<int> arr(n);
    vector<int> cost(n);

    cout << "Enter the elements of the array: ";
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    cout << "Enter the cost values for each element: ";
    for (int i = 0; i < n; i++)
    {
        cin >> cost[i];
    }

    cout << "Enter the value of k: ";
    cin >> k;

    int result = maxCost(arr, cost, k);
    cout << "Maximum possible sum of costs: " << result << endl;

    return 0;
}
