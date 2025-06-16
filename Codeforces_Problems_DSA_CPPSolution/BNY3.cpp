#include <bits/stdc++.h>
using namespace std;

vector<long> bitwiseEquations(vector<long> a, vector<long> b) 
{
    int n = a.size();
    vector<long> ans(n);

    for (int i = 0; i < n; i++) 
    {
        if (a[i] < b[i]) 
        {
            ans[i] = 0;
            continue;
        }

        long x = 0, y = 0;
        long diff = (a[i] - b[i]) / 2;

        for (int j = 0; j < 64; j++) 
        {
            if (b[i] & (1LL << j)) 
            {
                if ((diff & (1LL << j)) == 0) 
                {
                    y |= (1LL << j);
                } 
                else 
                {
                    x = 0;
                    y = 0;
                    break;
                }
            } 
            else 
            {
                if ((diff & (1LL << j))) 
                {
                    x |= (1LL << j);
                    y |= (1LL << j);
                }
            }
        }

        ans[i] = 2 * x + 3 * y;
    }

    return ans;
}
