#include<bits/stdc++.h>
using namespace std;

void solve(){
    int n;
    cin>>n;
    vector<long long> arr(n);
    for(int i = 0;i<n;i++){
        cin>>arr[i];
    }
    if((2*arr[0]-arr[1])<0 || (2*arr[0]-arr[1])%(n+1)!=0){
        cout<<"NO"<<endl;
       return;
    }
    long long x2 = (2*arr[0]-arr[1])/(n+1);
    long long x1 = arr[0]-n*x2;
    if(x1<0){
        cout<<"NO"<<endl;
        return;
    }
    bool flag = true;
    for(long long i = 1;i<=n;i++){
        if(arr[i-1]-i*x1 -(n-i+1)*x2!=0){
            flag = false;
        }
    }
    if(flag){
        cout<<"YES"<<endl;
    } else {
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