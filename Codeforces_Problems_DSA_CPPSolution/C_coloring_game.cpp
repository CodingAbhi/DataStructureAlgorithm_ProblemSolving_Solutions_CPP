#include<bits/stdc++.h>
using namespace std;


void solve(){
    int n;
    cin>>n;
    vector<int> arr(n);
    for(int i = 0; i < n; i++){
        cin>>arr[i];
    }
    long long ans = 0;
    for(int i = 0;i<n;i++){

        for(int j = i+1;j<n-1;j++){
            auto it = lower_bound(arr.begin()+j+1,arr.end(),arr[i]+arr[j]);
            int end = it-(arr.begin()+j+1);
            if(end ==0 ) continue;

            it = upper_bound(arr.begin()+j+1,arr.begin()+j+end+1,arr[n-1]-(arr[i]+arr[j]));
            ans+=(arr.begin()+j+end+1)-it;
        }
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