#include <bits/stdc++.h>
using namespace std;
int main()
{
    int a[1000];
    int n;
    cin >> n;
    for (int i = 0; i <= n - 1; i++)
    {
        cin >> a[i];
    }
    int num;
    cout << "Enter number you want to check -";
    cin >> num;
    for (int i = 0, m = 0; i <= n - 1; i++)
    {
        if (a[i] == num)
        {
            cout << "yes it is available in array at index - " << i << endl;
            break;
        }
    }
    if (i == n)
    {
        cout << " number is not in the array";
    }
}