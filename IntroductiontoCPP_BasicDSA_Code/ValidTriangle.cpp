#include<iostream>
using namespace std;
int main(){
    double a, b, c;
    cin >> a>>b>>c;
    if(((a+b)>c)&&((b+c)>a)&&((c+a)>b))
    {
        cout<<"valid Triangle";
    } 
    else {
        cout << "invalid Triangle";
        } 
        
}