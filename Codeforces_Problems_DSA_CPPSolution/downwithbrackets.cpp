#include<bits/stdc++.h>
using namespace std;

void solve(){
    string s;
    cin>>s;
    int full = 0;
    int ch = 0;
    for(char c: s){
        ch += c=='('? +1:-1;
        // cout<<"CHO VAL"<<ch<<endl;
        if(ch==0){
            full++;
        }
    }
    if(full>1){
        cout<<"YES";
    }else{
        cout<<"NO";
    }
}


int main(){
    int t;
    cin>> t;
    while(t--){
        solve();
        cout<<endl;
    }
}
