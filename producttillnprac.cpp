#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin >> n;
    int i = 1;
    int product = 1;
    while (i <= n)
    {
        product = product * i;
        i++;
    }
    cout << product;
}