#include <bits/stdc++.h>
using namespace std;
#include "stackusingarray1.cpp"
int main()
{
    stackusingarray s(4);
    s.push(10);
    s.push(20);
    s.push(30);
    s.push(40);

    cout << s.pop() << endl;
    cout << s.top() << endl;
    cout << s.isEmpty() << endl;
    s.push(50);
    cout << s.top() << endl;
    cout << s.size() << endl;
}