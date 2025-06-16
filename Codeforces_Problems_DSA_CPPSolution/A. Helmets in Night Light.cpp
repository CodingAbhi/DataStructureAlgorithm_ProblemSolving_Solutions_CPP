#include<bits/stdc++.h>
using namespace std;
int solve(){
int n,cst;
cin>>n>>cst;
vector<pair<int,int>>arr(n);
for(int i = 0;i<n;i++){
   cin>> arr[i].second;
}
for(int i = 0;i<n;i++){
   cin>> arr[i].first;
}
sort(arr.begin(),arr.end());
map<int,int>mp;
mp[cst]=n+100;
int ans = 0;
for(auto it:arr){
long long mini = mp.begin()->first;
ans+=mini;
mp[mini]--;
mp[it.first]+=it.second;
if(mp[mini]==0) mp.erase(mini);

}
return ans;


}
int main(){
    int t;
    cin>>t;
    while(t--){
      cout<< solve();
        cout<<endl;
    }
    return 0;
}