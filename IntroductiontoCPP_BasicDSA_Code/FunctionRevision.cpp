#include <bits/stdc++.h>
using namespace std;
int intfunc(int a)
{
    a = a + 10;
    return a;
}
void printfunc(int k)
{
    int i = 1;
    while (i <= k)
    {
        cout << i << endl;
        i++;
    }
}
int main()
{
    int n;
    cin >> n;
    int output = intfunc(n);
    cout << output << endl;
    printfunc(n);
}