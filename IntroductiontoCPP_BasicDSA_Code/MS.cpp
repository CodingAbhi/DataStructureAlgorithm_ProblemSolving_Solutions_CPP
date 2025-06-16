#include <bits/stdc++.h>
using namespace std;
int func1(int x, int y)
{
    if (x == 0)
    {
        return y;
    }
    else
    {
        return func1(x - 1, x + y) + x;
    }
}
int main()
{
    int x = 3;
    int y = 5;
    cout << func1(x, y);
}