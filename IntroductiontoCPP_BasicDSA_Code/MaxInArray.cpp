#include <bits/stdc++.h>
using namespace std;
int main()
{
    int arr[1000] = {0};
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    int max = INT_MIN;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }
    cout << "Max in the array is = " << max;
}