#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

int getMaximumXORFrequency(vector<int> &arr, int val)
{
    unordered_map<int, int> mp;
    int n = arr.size();
    int ans = 0;
    int preXOR = 0;
    for (int i = 0; i < n; ++i)
    {
        preXOR ^= arr[i];
        if (mp.find(preXOR ^ val) != mp.end())
        {
            ans = max(ans, mp[preXOR ^ val] + 1);
        }
        if (mp.find(preXOR) != mp.end())
        {
            mp[preXOR] = max(mp[preXOR], i - 1);
        }
        else
        {
            mp[preXOR] = i;
        }
    }
    return ans;
}

int main()
{
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> arr[i];
    }
    int val;
    cin >> val;

    cout << getMaximumXORFrequency(arr, val) << endl;

    return 0;
}