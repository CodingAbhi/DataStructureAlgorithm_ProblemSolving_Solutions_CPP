#include <bits/stdc++.h>
using namespace std;
int main()
{
    int a[1000];
    int n;
    cin >> n;
    int i;
    for (i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    int largest = INT_MIN;
    int smallest = INT_MAX;
    for (i = 0; i < n; i++)
    {
        if (a[i] > largest)
        {
            largest = a[i];
        }
        if (a[i] < smallest)
        {
            smallest = a[i];
        }
    }
    cout << "largest value - " << largest << endl;
    cout << "smallest value - " << smallest;
}