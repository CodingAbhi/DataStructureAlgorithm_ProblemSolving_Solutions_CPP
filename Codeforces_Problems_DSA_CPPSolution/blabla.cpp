#include <bits/stdc++.h>
using namespace std;

int main()
{
    // Write your code here
    string s;
    cin >> s;
    int n = s.length();
    for (int i = 0; i < n; i++)
    {
        if (i == 0 && s[i] == '9')
        {
            continue;
        }
        if (s[i] >= '5')
        {
            char c = s[i];
            s[i] = '9' - c + '0';
        }
    }
    cout << s << endl;
}
