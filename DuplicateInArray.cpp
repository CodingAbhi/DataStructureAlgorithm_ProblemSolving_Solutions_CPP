#include <bits/stdc++.h>
using namespace std;
void Duplicate(int n, int a[])
{
    for (int i = 0; i < n; i++)
    {

        for (int j = i; j < n; j++)
        {
            if (i != j && a[i] == a[j])
            {
                cout << a[i];
                break;
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
    Duplicate(n, a);
}