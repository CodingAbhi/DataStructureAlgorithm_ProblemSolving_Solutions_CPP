#include<bits/stdc++.h>
using namespace std;


void solve(){
    int n,k;
    cin>>n>>k;
    string s;
    cin>>s;
    int arr[26] = {0};

    for(int i = 0;i<n;i++){
        arr[s[i]-'a']++;
    }
    int sum = 0;
     for(int i = 0;i<26;i++){
        sum+=arr[i]%2;
    }
    if(sum-k>1){
        cout<<"NO"<<endl;
        return;
    }
    cout<<"YES"<<endl;

}

int main(){
    int t;
    cin>>t;
    while(t--){
        solve();
    }
}