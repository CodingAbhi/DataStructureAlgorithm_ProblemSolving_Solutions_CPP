#include <bits/stdc++.h>
using namespace std;

int *out = malloc(Q * sizeof(int));
*out_n = 0;
for (int i = 0; i < Q; i++)
{
    int indx = Queries[i][0];
    int val = Queries[i][1];
    int I = indx;

    if (indx <= N)
    {
        int OR = A[indx - 1];
        while (I <= N)
        {
            OR = OR | A[I - 1];
            if (OR >= val)
            {
                break;
            }
            I++;
        }
    }
    if (I > N)
    {
        I = -1;
    }
    out[i] = I;
    *out_n = *out_n + 1;
}
return out;
