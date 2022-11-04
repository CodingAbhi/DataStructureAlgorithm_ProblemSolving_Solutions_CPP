#include <bits/stdc++.h>
using namespace std;
void PS(int n, int x, int a[])
{
    int Pair = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (a[i] + a[j] == x)
            {
                Pair++;
            }
        }
    }
    cout << Pair << endl;
}

int main()
{
    int n;
    cin >> n;
    int x;
    cin >> x;
    int a[1000] = {0};
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    PS(n, x, a);
}