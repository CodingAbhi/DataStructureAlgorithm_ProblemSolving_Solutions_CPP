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
    int top = 0;
    int bottom = j - 1;
    int left = 0;
    int right = i - 1;
    while ((top <= bottom) && (left <= right))
    {
        for (int i = left; i <= right; i++)
        {
            cout << a[i][top] << " ";
        }
        top++;
    }
}
