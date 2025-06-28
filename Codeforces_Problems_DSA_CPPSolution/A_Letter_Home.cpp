#include<bits/stdc++.h>
using namespace std;


void solve(){
    int n, s;
    cin>>n>>s;
  
    vector<int> a(n);
    int mini = INT_MAX;
    int maxi = INT_MIN;
    for(int i = 0; i < n; i++){
        cin>>a[i];
        mini = min(mini, a[i]);
        maxi = max(maxi, a[i]);
    }
    int d1 = abs(maxi - s);
    int d2 = abs(mini - s);

    int ans;
    if(s<=mini){
        ans=d2+ abs(maxi-mini);
    }else if(s>=maxi){
        ans=d1+ abs(maxi-mini);
    }
    else{ if(d1<d2){
         ans = d1*2 + (abs(s-mini));
    }else{
         ans = d2*2 + (abs(s-maxi));
    }}
    cout<<ans<<endl;
}
int main(){
    int t;
    cin>>t;
    while(t--){
        solve();
    }
}