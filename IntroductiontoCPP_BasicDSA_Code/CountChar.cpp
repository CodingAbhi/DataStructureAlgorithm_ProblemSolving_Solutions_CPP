#include <bits\stdc++.h>
using namespace std;
int main()
{
    char i;
    i = cin.get();
    int charcount = 0;
    while (i != '$')
    {
        charcount++;
        i = cin.get();
    }
    cout << charcount;
}