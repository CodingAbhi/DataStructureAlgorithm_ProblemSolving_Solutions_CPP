#include <bits/stdc++.h>
using namespace std;
int Find(int arr[], int n, int x)
{
    for (int i = 0; i < n; i++)
    {
        if (arr[i] == x)
        {
            cout << "Element is found at - ";
            return i;
            break;
        }
    }
    return 0;
}
int main()
{
    int arr[1000];
    int n;
    cout << "Enter n : ";
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    int x;
    cout << "Enter Number to find : ";
    cin >> x;
    cout << Find(arr, n, x);
}