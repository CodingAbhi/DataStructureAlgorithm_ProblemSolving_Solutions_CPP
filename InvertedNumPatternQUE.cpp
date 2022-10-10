#include<bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cin >> n;
    int i=1;
        int k=1;
    while(i<=n){
        int j=1;
        while(j<=n-i+1){
            cout<<n-k+1;
            j++;
        }
        cout<<endl;
        i++;
        k++;
    }
}