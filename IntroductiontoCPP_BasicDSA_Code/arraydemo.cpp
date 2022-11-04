#include <bits/stdc++.h>
using namespace std;
int main()
{
    int a[10] = {1, 2, 3};
    for (int i = 0; i < 5; i++)
    {
        cin >> a[i];
    }
    a[5] = {100};
    for (int i = 0; i < 10; i++)
    {
        cout << a[i] << endl;
    }
    cout << sizeof(a) << endl;
    int b = sizeof(a) / sizeof(int);
    cout << b << endl;
}