#include <iostream>
using namespace std;
int inc1(int a)
{
    a++;
    return a;
}
int main()
{
    int i;
    cin >> i;
    int output = inc1(i);
    cout << output;
}