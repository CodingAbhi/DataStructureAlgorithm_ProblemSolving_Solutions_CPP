#include <bits/stdc++.h>
using namespace std;
int main()
{
    long long i, j;
    cin >> i >> j;
    long long a[i][j];
    for (int n = 0; n < i; n++)
    {
        for (int m = 0; m < j; m++)
        {
            cin >> a[n][m];
        }
    }
    for (int n = 0; n < i; n++)
    {
        for (int m = 0; m < j; m++)
        {
            cout << a[n][m];
        }
        cout << endl;
    }
}