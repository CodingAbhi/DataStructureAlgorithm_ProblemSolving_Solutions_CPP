#include <bits/stdc++.h>

using namespace std;
int main()
{
    int x;
    cin >> x;
    if (x < 0)
    {
        cout << "NO" << endl;
    }
    int number = x;
    int reverse = 0;
    while (number)
    {
        reverse = reverse * 10 + number % 10;
        number = number / 10;
    }
    if (x == reverse)
    {
        cout << "YES" << endl;
    }
    else
    {
        cout << "NO" << endl;
    }
}
