#include <bits\stdc++.h>
using namespace std;
int main()
{
    int n;
    cin >> n;
    int i = 0;
    int j = 1;
    while (i <= n)
    {
        int k = i + j;
        cout << i << " ";
        i = j;
        j = k;
    }
}