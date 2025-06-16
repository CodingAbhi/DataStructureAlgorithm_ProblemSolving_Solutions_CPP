#include<bits/stdc++.h>
using namespace std;

void solve(){
    string s;
    cin>>s;
    int a = stoi(s);
    bool ch = true;
    for(int i = 0;i<=99;i++){
        for(int j = 0;j<=99;j++){
            int x = (i+j)*(i+j);
            if(x==a){
                cout<<i<<' '<<j<<endl;
                ch = false;
                break;
            }
        }
        if(ch==false){
            break;
        }
    }
    if(ch){
        cout<<-1<<endl;
    }
}

int main(){
    int t;
    cin>>t;
    while(t--){
        solve();
    }
}