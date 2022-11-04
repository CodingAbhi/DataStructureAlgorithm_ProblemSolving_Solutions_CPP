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
    int min = INT_MAX;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] < min)
        {
            min = arr[i];
        }
    }
    cout << "Min in the array is = " << min;
}