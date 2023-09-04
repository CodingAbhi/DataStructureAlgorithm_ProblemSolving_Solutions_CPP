#include <bits/stdc++.h>
using namespace std;
void print(int *p)
{
    cout << *p << endl;
}
void increment(int *p)
{
    p = p + 1;
}
void incval(int *p)
{
    (*p)++;
}
int main()
{
    int a = 10;
    int *p = &a;
    cout << p << endl;
    print(p);
    increment(p);
    print(p);
    cout << p << endl;
    incval(p);
    cout << *p << endl;
}