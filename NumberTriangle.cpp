#include <bits\stdc++.h>
using namespace std;
int main()
{
    int n;
    cin >> n;
    int i = 1;
    while (i <= n)
    {
        int s = 1;
        while (s <= n - i)
        {
            cout << " ";
            s++;
        }
        int j = 1;
        int k = i;
        while (j <= i)
        {
            cout << k;
            k++;
            j++;
        }
        int m = i - 1;
        int o = (2 * i - 2);
        while (m >= 1)
        {
            cout << o;
            o--;
            m--;
        }
        cout << endl;
        i++;
    }
}