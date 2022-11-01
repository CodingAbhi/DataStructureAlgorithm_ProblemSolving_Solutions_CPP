#include <bits\stdc++.h>
using namespace std;
int main()
{
    string s = "Abhishek";
    string s1(s, 4, 4);
    cout << s1 << endl;
    string s2 = s.substr(0, 4);
    cout << s2 << endl;
    if (s1.compare(s2) == 0)
    {
        cout << s1 << " is equal to " << s2 << endl;
    }
    else
    {
        cout << s1 << " is not equal to " << s2 << endl;
    }
}