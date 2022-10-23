#include <bits/stdc++.h>
using namespace std;
void bubble_sort(int a[], int n)
{
    for (int j = 0; j < n - 1; j++)
    {
        if (a[j] > a[j + 1])
        {
            swap(a[j + 1], a[j]);
        }
    }
}

int main()
{
    int a[1000] = {0};
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    bubble_sort(a, n);
    for (int i = 0; i < n; i++)
    {
        cout << a[i] << ",";
    }
}
// comment;