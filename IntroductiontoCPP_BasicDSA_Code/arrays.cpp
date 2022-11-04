#include <bits/stdc++.h>
using namespace std;
int main()
{
    int arr[1000] = {0};
    int n;
    cout << "Enter number of desired length ";
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << endl;
    }
}