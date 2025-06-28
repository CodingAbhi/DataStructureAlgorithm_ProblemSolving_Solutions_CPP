#include<bits/stdc++.h>
using namespace std;

void solve(){
    long long a,b,n;
    cin>>a>>b>>n;
    vector<long long> arr(n);
    for(long long i = 0;i<n;i++){
        cin>>arr[i];
    }
    long long ans = b;
    for(long long i = 0;i<n;i++){
       ans+=min(arr[i], a-1);
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