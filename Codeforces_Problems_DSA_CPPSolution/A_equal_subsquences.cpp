#include<bits/stdc++.h>
using namespace std;

void solve(){
    int n,k;
    cin>>n>>k;
    int t = n -k;
    while(k--){
        cout<<1;
    }
    while(t--){
        cout<<0;
    }
    cout<<endl;
}

int main(){
    int t;
    cin>>t;

    while(t--){
        solve();
    }
}