#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin >> n;
    int a[1000] = {0};
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    for (int j = 0; j < n; j++)
    {
        for (int k = j; k < n; k++)
        {
            for (int m = j; m <= k; m++)
            {
                cout << a[m];
            }
            cout << endl;
        }
    }
}