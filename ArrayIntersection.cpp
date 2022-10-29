#include <bits/stdc++.h>
using namespace std;

void intersection(int n, int m, int a[], int arr[])
{

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (a[i] == arr[j])
            {
                cout << arr[j] << endl;
                break;
            }
        }
    }
}

int main()
{
    int n;
    cin >> n;
    int a[1000] = {0};
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    int m;
    cin >> m;
    int arr[1000] = {0};
    for (int i = 0; i < m; i++)
    {
        cin >> arr[i];
    }
    intersection(n, m, a, arr);
}
