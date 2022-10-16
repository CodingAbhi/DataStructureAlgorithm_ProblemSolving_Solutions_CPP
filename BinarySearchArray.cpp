#include <bits/stdc++.h>
using namespace std;
int Binaryfunc(int a[], int n, int key)
{
    int s = 1;
    int e = n - 1;
    while (s <= e)
    {
        int mid = (s + e) / 2;
        if (mid > key)
        {
            e = mid - 1;
        }
        if (mid < key)
        {
            s = mid + 1;
        }
        if (mid == key)
        {
            return mid;
            break;
        }
    }
    return -1;
}
int main()
{
    int a[1000];
    int n;
    cin >> n;
    int key;
    cout << "Enter Key";
    cin >> key;
    for (int i = 0; i <= n - 1; i++)
    {
        cin >> a[i];
    }
    cout << Binaryfunc(a, n, key) << endl;
}