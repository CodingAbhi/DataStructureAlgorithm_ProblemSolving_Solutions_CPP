#include <iostream>
using namespace std;
int main()
{
    int x = 10;
    int y = 20;
    if (x++ > 10 && ++y > 20)
    {
        cout << "inside if";
    }
    else
    {
        cout << "inside else ";
    }
    cout << x << " " << y;
}