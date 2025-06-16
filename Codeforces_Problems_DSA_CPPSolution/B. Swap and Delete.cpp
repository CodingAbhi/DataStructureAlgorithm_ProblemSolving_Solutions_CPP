#include<bits/stdc++.h>
using namespace std;
void solve(){
    string s;
    cin>>s;
    int n = s.length();
    int zeros=0,ones=0;
    for(int i = 0;i<n;i++){
        if(s[i]=='0'){
            zeros++;
        }else{
            ones++;
        }
    }
    for(int i = 0;i<n;i++){
        if(s[i]=='0'){
            if(ones){
                ones--;
            }else{
                break;
            }
        }else{
            if(zeros){
                zeros--;
            }else{
                break;
            }
        }
    }
    cout<<abs(ones+zeros)<<endl;
}

int main(){
    int t;
    cin>>t;
    while(t){
        solve();
        t--;
    }
    return 0;
}