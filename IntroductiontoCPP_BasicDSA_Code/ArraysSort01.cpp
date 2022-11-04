#include <bits/stdc++.h>
using namespace std;
void sort(int n, int a[])
{
    for (int i = 0; i < n; i++)
    {
        for (int j = n - 1; j > i; j--)
        {
            if (a[i] == 1 && j >= 0)
            {
                swap(a[i], a[j]);
            }
        }
    }
    for (int k = 0; k < n; k++)
    {
        cout << a[k] << " ";
    }
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
    sort(n, a);
}