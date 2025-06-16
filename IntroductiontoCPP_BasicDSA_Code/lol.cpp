#include <bits/stdc++.h>
using namespace std;
void merge(int arr[], int l, int mid, int r)
{
    vector<int> temp;
    int left = l;
    int right = mid + 1;
    while (left <= mid && right <= r)
    {
        if (arr[left] <= arr[right])
        {
            temp.push_back(arr[left]);
            left++;
        }
        else
        {
            temp.push_back(arr[right]);
            right++;
        }
    }
    while (left <= mid)
    {
        temp.push_back(arr[left]);
        left++;
    }
    while (right <= r)
    {
        temp.push_back(arr[right]);
        right++;
    }
    // for (int i = left; left <= right; left++)
    // {
    //     arr[i - left] = temp[i];
    // }
    for (auto i = temp.begin(); i < temp.end(); i++)
    {
        cout << *i << " ";
    }
    cout << endl;
}
void mergeSort(int arr[], int l, int r)
{

    // Write Your Code Here
    if (l >= r)
    {
        return;
    }
    int mid = (l + r) / 2;

    mergeSort(arr, l, mid);
    mergeSort(arr, mid + 1, r);
    merge(arr, l, mid, r);
}

int main()
{
    int n;
    cin >> n;
    int l = 0;
    int r = n - 1;

    int arr[n] = {0};
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    mergeSort(arr, l, r);
    for (int i = l; i <= r; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}