#include <bits/stdc++.h>
using namespace std;
void unq(int n, int a[])
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i != j && a[i] == a[j])
            {
                break;
            }
            if (j == n - 1)
            {
                cout << a[i];
            }
        }
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
    unq(n, a);
}