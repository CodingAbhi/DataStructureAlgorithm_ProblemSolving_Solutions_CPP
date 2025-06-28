#include<bits/stdc++.h>
using namespace std;


void solve(){
    int n;
    cin>>n;
    string s;
    cin>>s;
    unordered_map<char, int> freq,lfre;
    for(int i = 0;i<n;i++){
        freq[s[i]]++;
    }
    
    bool ans = false;
    for(int i = 0;i<n;i++){
        freq[s[i]]--;
     if(i>0&&i<n-1){   if(freq[s[i]] > 0 || lfre[s[i]]>0){
            ans  = true;
            break;
        }}
        lfre[s[i]]++;
    }
    if(ans){
        cout<<"Yes"<<endl;
    }else{
        cout<<"No"<<endl;
    }
}
int main(){
    int t;
    cin>>t;
    while(t--){
        solve();
    }
}