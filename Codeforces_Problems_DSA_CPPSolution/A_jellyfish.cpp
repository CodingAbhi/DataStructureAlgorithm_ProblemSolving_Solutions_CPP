#include<bits/stdc++.h>
using namespace std;

void solve(){
    int a,b,c,d;
    cin>>a>>b>>c>>d;
    int gellytot = min(a,c);
    int flowertot = min(b,d);
    if(gellytot>flowertot){
        cout<<"Gellyfish";
    }else if(gellytot==flowertot){
        cout<<"Gellyfish";
    }
    else{
        cout<<"Flower";
    }
}
int main(){
    int t;
    cin>>t;
    while(t--){
        solve();
        cout<<endl;
    }
}