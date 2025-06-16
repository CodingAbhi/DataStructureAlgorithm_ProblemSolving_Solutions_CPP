#include<bits/stdc++.h>
using namespace std;

void solve(){
    int n,m;
    cin>>n>>m;
    if(n==m==1){
        cout<<1;
        return;
    }
    vector<int> arr(n);
    for(int i = 0;i<n;i++){
        cin>>arr[i];
    }
    int maxi = arr[0];
    for(int i = 0;i<n-1;i++){
        maxi = max(maxi,arr[i+1]-arr[i]);
    }
    int k= 2*abs(arr[n-1]-m);
    // cout<<"maxi"<<maxi<<" k"<<k<<endl;
    cout<<max(maxi,k)<<endl;
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