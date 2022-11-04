#include <bits/stdc++.h>
using namespace std;
void selection_sort(int a[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int min_index = i;
        for (int j = i; j < n - 1; j++)
        {
            if (a[j] < a[min_index])
            {
                min_index = j;
                swap(a[j], a[min_index]);
            }
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
    for (int i = 0; i <= n - 1; i++)
    {
        cout << a[i] << ",";
    }
    selection_sort(a, n);
}