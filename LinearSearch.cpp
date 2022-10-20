#include <bits/stdc++.h>
using namespace std;
void Find(int arr[], int n, int x)
{
    int m = 0;
    for (int i = 0; i < n; i++, m++)
    {
        if (arr[i] == x)
        {
            cout << "Element is found at - " << i;
            break;
        }
    }
    if (m == n)
        cout << "Element is not in the given Array";
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
    Find(arr, n, x);
}