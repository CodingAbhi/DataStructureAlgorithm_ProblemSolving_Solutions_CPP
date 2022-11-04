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
    int arr_sum = 0;
    for (int i = 0; i < n; i++)
    {
        arr_sum = arr_sum + arr[i];
    }
    cout << "sum of all Array Element is = " << arr_sum << endl;
}