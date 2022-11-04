#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin >> n;
    int arr[1000] = {0};
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    int max = INT_MIN;
    int current_sum = 0;
    for (int i = 0; i < n; i++)
    {
        current_sum = current_sum + arr[i];
        if (current_sum > max)
        {
            max = current_sum;
        }
        if (current_sum < 0)
        {
            current_sum = 0;
        }
    }
    cout << max << endl;
}