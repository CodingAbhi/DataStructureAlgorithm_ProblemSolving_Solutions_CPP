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
    int currentsum = 0;
    int max = INT_MIN;
    for (int i = 0; i < n; i++)
    {
        currentsum = currentsum + a[i];
        if (currentsum > max)
        {
            max = currentsum;
        }
        if (currentsum < 0)
        {
            currentsum = 0;
        }
    }
    cout << max;
}
