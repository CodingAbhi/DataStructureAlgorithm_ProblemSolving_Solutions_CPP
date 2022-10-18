#include <bits/stdc++.h>
using namespace std;
int Binary_func(int a[], int n, int key)
{
    int s = 0;
    int e = n - 1;
    while (s <= e)
    {
        int mid = (s + e) / 2;
        if (a[mid] > key)
        {
            e = mid - 1;
        }
        if (a[mid] < key)
        {
            s = mid + 1;
        }
        if (a[mid] == key)
        {
            cout << "key is at index - ";
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
    for (int i = 0; i <= n - 1; i++)
    {
        cin >> a[i];
    }
    int key;
    cout << "Enter Key";
    cin >> key;
    cout << Binary_func(a, n, key) << endl;
}