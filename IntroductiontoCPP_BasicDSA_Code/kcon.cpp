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
    int k;
    cout << "k ? " << endl;
    cin >> k;
    int p = n * k;
    int b[10000] = {0};

    for (int m = 0; m < p; m++)
    {
        for (int i = 0; i < n; i++)
        {
            cin >> b[a[i]];
        }
    }
    for (int j = 0; j < p; j++)
    {
        cout << b[j] << ", ";
    }
    return 0;
}