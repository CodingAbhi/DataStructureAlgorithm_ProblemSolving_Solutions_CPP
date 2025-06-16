#include <bits/stdc++.h>
using namespace std;
#include "classfrac.cpp"
int main()
{

    fraction f1(10, 2);
    fraction f2(15, 4);
    f1.print();
    f2.print();
    // f1.add(f2);
    f1.print();
    f2.print();
    f1.multiply(f2);
    f1.print();
}