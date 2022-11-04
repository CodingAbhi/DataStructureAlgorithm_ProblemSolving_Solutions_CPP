#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    n = 4;
    int a[n] = {1, 2, 3, 4};
    int pre[n + 1];
    pre[0] = 0;
    for (int i = 1; i <= n; i++)
    {
        pre[i] = pre[i - 1] + a[i - 1];
    }
    for (int j = 0; j <= n; j++)
    {
        cout << pre[j] << " ";
    }

    return 0;
}