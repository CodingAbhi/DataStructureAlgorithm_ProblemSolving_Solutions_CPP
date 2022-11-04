#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin >> n;
    int nfactorial = 1;
    int i = 1;
    while (i <= n)
    {
        nfactorial = nfactorial * i;
        i++;
    }
    cout << nfactorial;
}