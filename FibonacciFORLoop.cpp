#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin >> n;
    int i = 0;
    int j = 1;
    int k;
    for (i = 0; i <= n; i = j, j = k)
    {
        cout << i << " ";
        k = i + j;
    }
}