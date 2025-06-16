#include <bits/stdc++.h>
using namespace std;
#include "classcomplex.cpp"
int main()
{
    mycomplex c1(3, 5);
    mycomplex c2(5, 4);
    c1.print();
    c2.print();
    // c1.add(c2);
    c1.multiply(c2);
    c1.print();
}