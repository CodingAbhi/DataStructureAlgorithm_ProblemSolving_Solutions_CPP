#include<bits/stdc++.h>
using namespace std;

void solve(){
    int n,k;
    cin>>n>>k;
    string s;
    cin>>s;
    int cntz = 0;
    int cnto =0;
    for(int i = 0;i<n;i++){
        if(s[i]-'0'==0){
            cntz++;
        }else{
            cnto++;
        }
    }
    int totpair = n/2;
    int reqbad = totpair - k;

  if(cntz< reqbad || cnto<reqbad){
    cout<<"NO"<<endl;
  }
   int remz = cntz - reqbad;
    int remo = cnto - reqbad;
   int zpair = remz/2;
   int opair = remo/2;
   int tgpair = zpair+opair;
   if(tgpair>=k){
    cout<<"YES"<<endl;
   }else{
    cout<<"NO"<<endl;
   }
    
   
}

int main(){
    int t;
    cin>>t;
    while(t--){
        solve();
    }
}