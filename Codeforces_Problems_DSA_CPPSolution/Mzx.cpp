#include <iostream>
#include <unordered_map>
using namespace std;

int max_equal_length(int arr[], int n, int k)
{
    unordered_map<int, int> count;
    int max_length = 0;
    for (int i = 0; i < n; i++)
    {
        for (int x = -k; x <= k; x++)
        {
            int modified_num = arr[i] + x;
            count[modified_num]++;
            max_length = max(max_length, count[modified_num]);
        }
    }
    return max_length;
}

int main()
{
    int T;
    cin >> T;
    for (int i = 0; i < T; i++)
    {
        int n, k;
        cin >> n >> k;
        int arr[n];
        for (int j = 0; j < n; j++)
        {
            cin >> arr[j];
        }
        int result = max_equal_length(arr, n, k);
        cout << result << endl;
    }
    return 0;
}
