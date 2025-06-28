#include<bits/stdc++.h>
using namespace std;

void solve(){
    long long n;
    cin>>n;
    vector<long long> arr(n);
    for(long long i = 0; i < n; i++){
        cin>>arr[i];
    }
    if(n == 1){
        cout<<0<<endl;
        return;
    }
    
    long long first = arr[0];
    long long last = arr[n-1];
    long long ans = arr[n-1] - arr[0];
    for(long long i = 1; i < n; i++){
       ans = max(ans, (arr[i] - first));
    }
      for(long long i =0; i <n-1; i++){
       ans = max(ans, (last - arr[i]));
    }
    for(long long i = 0; i < n-1; i++){
        ans = max(ans, (arr[i] - arr[i+1]));
    }
    cout<<ans<<endl;
}

int main(){
    int t;
    cin>>t;
    while(t--){
        solve();
    }
}