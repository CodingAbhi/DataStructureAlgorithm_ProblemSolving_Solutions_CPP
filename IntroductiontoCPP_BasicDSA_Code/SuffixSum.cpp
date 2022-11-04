#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n = 4;
    int a[n] = {1, 2, 3, 4};
    int suffix[n];
    suffix[3] = a[3];
    for (int i = n - 1; i >= 0; i--)
    {
        suffix[i] = suffix[i + 1] + a[i];
    }
    for (int k = 0; k < n; k++)
    {
        cout << suffix[k] << " ";
    }
}