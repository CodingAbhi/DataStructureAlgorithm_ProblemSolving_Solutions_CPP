#include <bits/stdc++.h>
using namespace std;
int main()
{
    set<int> s;
    int a[] = {1, 2, 3, 4, 3, 5, 6, 7, 6, 8};
    for (int i = 0; i < 10; i++)
    {
        s.insert(a[i]);
    }
    set<int>::iterator it;
    cout << "SET : " << endl;
    for (it = s.begin(); it != s.end(); it++)
    {
        cout << *it << endl;
    }
    cout << endl;

    if (s.find(5) == s.end())
    {
        cout << "Element not found" << endl;
    }
    else
    {
        cout << "Element found";
    }
}