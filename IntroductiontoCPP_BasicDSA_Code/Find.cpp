#include <bits/stdc++.h>
using namespace std;
int main()
{

    int arr[] = {1, 4, 6, 5, 4};
    int n = sizeof(arr) / sizeof(int);
    int key;
    cin >> key;
    auto it = find(arr, arr + n, key);
    cout << it - arr << endl;
}
