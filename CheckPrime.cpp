#include<iostream>
using namespace std;
int main(){
    int n;
    cin >> n;
    int div = 2;
    while(div < n){
        if(n%div==0){
            cout<<"it's not PRIME";
            break;
        }else{ div = div+1 ;}
    }
    if(div>=n){cout<<"it's a Prime";}
}