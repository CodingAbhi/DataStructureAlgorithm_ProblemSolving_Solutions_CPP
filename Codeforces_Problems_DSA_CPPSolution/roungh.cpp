//{ Driver Code Starts
// Initial Template for C++

#include <bits/stdc++.h>
using namespace std;

// } Driver Code Ends
// User function Template for C++
class Solution
{
public:
    string reverseWord(string s)
    {
        int n = s.size() - 1;
        string r[n];
        int i = 0;

        while (i <= n)
        {
            char p = s[i];
            s[i] = s[n];
            s[n] = p;
            i++;
            n--;
        }
        return s;

        //{ Driver Code Starts.

        // int main()
        // {

        //     int t;
        //     cin >> t;
        //     while (t--)
        //     {
        //         string s;
        //         cin >> s;
        //         Solution ob;
        //         cout << ob.reverseWord(s) << endl;
        //     }
        //     return 0;
        // }
    }
};
int main()
{
    string s;
    cin >> s;
    Solution ob;
    cout << ob.reverseWord(s) << endl;
}

// } Driver Code Ends