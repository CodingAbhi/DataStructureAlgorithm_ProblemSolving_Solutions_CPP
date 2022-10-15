#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin >> n;
    cout << "choose 1 for sum till n or choose 2 for n factorial";
    int c;
    cin >> c;

    // sum
    if (c == 1)
    {
        int i = 1;
        int sum = 0;
        while (i <= n)
        {

            sum = sum + i;
            i++;
        }
        cout << sum;
    }
    else if (c == 2)
    {
        // factorial
        int k = 1;
        int product = 1;
        while (k <= n)
        {

            product = product * k;
            k++;
        }
        cout << product;
    }
}