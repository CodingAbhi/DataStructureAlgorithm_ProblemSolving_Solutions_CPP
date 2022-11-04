#include <bits/stdc++.h>
using namespace std;
void TripletSum(int n, int a[], int x)
{
    int Pair = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            for (int k = j + 1; k < n; k++)
            {
                if ((a[i] + a[j] + a[k]) == x)
                {
                    Pair++;
                }
            }
        }
    }
    cout << Pair;
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
    TripletSum(n, a, x);
}