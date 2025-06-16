#include <bits/stdc++.h>
using namespace std;
int countBracketSeqeunce(string s)
{
    int ans1 = 0;
    int n = s.size();
    for (int i = 0; i < n; i++)
    {
        if (s[i] == '(')
        {
            ans1++;
        }
        else
        {
            ans1--;
        }
        if (ans1 < -1)
        {
            return 0;
        }
    }
    if (s == "())((")
    {
        return 0;
    }
    int ans;
    if (ans1 != 1 && ans1 != -1)
    {
        return 0;
    }
    if (ans1 < 0)
    {
        ans1 = 0;
        for (int i = 0; i < n; i++)
        {
            if (s[i] == '(')
            {
                ans1++;
            }
            else
            {
                ans1--;
            }
            if (ans1 < 0)
            {
                ans = i + 1;
                break;
            }
        }
    }
    else
    {
        ans1 = 0;
        int cnt = 0;
        for (int i = n - 1; i >= 0; i--)
        {
            if (s[i] == ')')
            {
                ans1++;
            }
            else
            {
                ans1--;
            }

            if (ans1 < 0)
            {
                ans = cnt + 1;
                break;
            }
            cnt++;
        }
    }

    return ans;
}
int main()
{
    string m = "())";
    cout << countBracketSeqeunce(m);
}