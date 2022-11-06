#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin >> n;
    int count = 0;
    string s;

    cin >> s;

    for (int i = 0; i < n; i++)
    {
        if (s[i] == '1')
        {
            s[i] = '0';
            count++;
        }
    }
    cout << (10 * n) + (count * 1);
}