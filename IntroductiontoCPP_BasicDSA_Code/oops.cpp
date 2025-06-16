#include <bits/stdc++.h>
using namespace std;
#include "studentclass.cpp"
int main()
{
    /* student *s1 = new student(96, 976);
     student *s3 = new student(50);
     student s2(2, 98);
     s1->display();
     s2.display();
     (*s3).display();
     student s4(s2);
     s4.display();
     student *s5 = new student(*s1);
     (*s5).display();
     student *s6 = new student(s2);
     (*s6).display();*/
    student s1(12, 349);
    student s2(2, 352);
    s1.display();
    s2.display();
    s2 = s1;
    s2.display();
    student *s3 = new student(23, 985);
    s3->display();
    *s3 = s2;
    s3->display();
    delete s3;
}
