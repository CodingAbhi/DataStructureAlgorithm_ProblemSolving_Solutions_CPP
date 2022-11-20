#include <bits/stdc++.h>
using namespace std;

int main()
{
    int x;
    cin >> x;
    int n, m;
    cin >> n >> m;
    long long a[n][m];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> a[i][j];
        }
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (x == a[i][j])
            {
                cout << "Element found at = ";
                cout << i << ":" << j << endl;
            }
        }
    }
}