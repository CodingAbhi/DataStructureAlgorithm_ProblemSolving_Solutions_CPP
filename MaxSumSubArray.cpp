#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin >> n;
    int a[1000] = {0};
    for (int l = 0; l < n; l++)
    {
        cin >> a[l];
    }
    int sum = INT_MIN;
    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            for (int k = i; k <= j; k++)
            {
                if (sum < a[j])
                {
                    sum = a[j];
                }
            }
        }
    }
    cout << sum << endl;
}