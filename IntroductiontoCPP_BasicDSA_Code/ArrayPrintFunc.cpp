#include <bits/stdc++.h>
using namespace std;
void print(int arr[], int n)
{
    cout << "print : " << endl;
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << endl;
    }
}
int main()
{
    int arr[1000] = {0};
    int n;
    cout << "Enter n : ";
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    print(arr, n);
}