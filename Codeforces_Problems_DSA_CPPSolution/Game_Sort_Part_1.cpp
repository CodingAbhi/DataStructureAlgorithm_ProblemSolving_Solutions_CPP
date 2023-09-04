#include <bits/stdc++.h>
using namespace std;

int main()
{
    int t;
    cin >> t;
    for (int i = 1; i <= t; i++)
    {
        int p;
        cin >> p;
        vector<string> parts(p);
        for (int j = 0; j < p; j++)
        {
            cin >> parts[j];
            sort(parts[j].begin(), parts[j].end());
        }
        string sorted_string;
        for (string s : parts)
        {
            sorted_string += s;
        }
        string input_string = sorted_string;
        sort(input_string.begin(), input_string.end());
        cout << "Case #" << i << ": ";
        if (input_string == sorted_string)
        {
            cout << "POSSIBLE\n";
            for (string s : parts)
            {
                cout << s << " ";
            }
            cout << "\n";
        }
        else
        {
            cout << "IMPOSSIBLE\n";
        }
    }
    return 0;
}
