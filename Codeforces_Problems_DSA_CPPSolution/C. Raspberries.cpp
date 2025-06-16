#include<bits/stdc++.h>
using namespace std;
int sok(int k,vector<int>arr){
    int cnt = 0;
    for(int i = 0;i<arr.size();i++){
        if(arr[i]%2==0){
            cnt++;
        }
    }
    if(cnt>=2){
        return 0;
    }else if(cnt==1){
        return 1;
    }else{
        return 2;
    }
}
void solve(){
int n,k;
cin>>n>>k;
vector<int> arr(n);
vector<int> res;
for(int i = 0;i<n;i++){
    cin>>arr[i];
    int m = arr[i]%k;
    if(arr[i]>k){ 
        if(m==0){
            res.push_back(0);
        }
        else{
        res.push_back(k-m);
        }}
    else if(arr[i]==1){ res.push_back(k-1);}
    else{ res.push_back(k-arr[i]);}
}
int mini=INT_MAX;
for(auto it: res){
    // cout<<it<<" ";
   mini=min(mini,it);
}

if(k==4){
    int q = sok(k,arr);
    cout<< min(q,mini);
    return;
}
cout<<mini;
}
int main(){
int t;
cin>>t;
while(t--){
    solve();
    cout<<endl;
}
return 0;
}