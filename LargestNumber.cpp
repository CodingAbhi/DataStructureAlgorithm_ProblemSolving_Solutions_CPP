#include<iostream>
using namespace std;
int main(){
    int a;
    int b;
    int c;
    cin >> a >> b >> c;
    if(a>b && a>c){
        cout<<"a";
    }else{if (b>a && b>c){cout<<"b";
    } else if ((a==b)&&(b==c))
    {cout<<"a, b and c are equal";}
    else{cout<<"c";
    }
}
}