#include <bits/stdc++.h>
using namespace std;
int main()
{
    set<int> s;
    int a[] = {0, 1, 2, 3, 4, 5, 6, 5};
    for (int i = 0; i < 8; i++)
    {
        s.insert(a[i]);
    }
    set<int>::iterator it;
    for (it = s.begin(); it != s.end(); it++)
    {
        cout << *it << endl;
    }
}
