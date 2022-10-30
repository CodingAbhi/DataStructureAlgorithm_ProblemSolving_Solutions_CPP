#include <bits/stdc++.h>
using namespace std;
int SecondLargest(int n, int a[])
{
    int max = a[0];
    for (int j = 0; j < n; j++)
    {
        if (a[j] > max)
        {
            max = a[j];
        }
    }
    int max2 = a[0];

    for (int i = 0; i < n; i++)
    {
        while (max2 < max)
        {
            if (a[i] > max2)
            {
                max2 = a[i];
                break;
            }
        }
    }
    cout << max2;
}
int main()
{
    int n;
    cin >> n;
    int a[1000] = {0};
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    SecondLargest(n, a);
}