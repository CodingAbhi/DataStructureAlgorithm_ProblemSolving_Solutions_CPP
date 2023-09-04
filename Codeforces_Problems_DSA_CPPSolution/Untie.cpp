#include <iostream>
#include <string>
#include <bits/stdc++.h>

using namespace std;

int main()
{
    int T;
    cin >> T;
    string xx;
    for (int t = 1; t <= T; t++)
    {
        string s;
        cin >> s;
        // string s;

        // s += temp.back();
        // s += temp;
        int cnt = 0;
        for (int i = 0; i < s.size() - 1; i++)
        {
            /* code */
            if (s[i] == s[i + 1])
            {

                cnt += 2;
                i++;
            }
        }
        if (cnt <= 1)
        {
            xx = "0";
        }
        else
        {

            xx = to_string((cnt / 2) + 1);
        }

        cout << "Case #" << t << ": " << xx << endl;
    }
    return 0;
}
