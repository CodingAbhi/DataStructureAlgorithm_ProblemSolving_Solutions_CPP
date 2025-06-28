#include<bits/stdc++.h>
using namespace std;


void solve(){
    int n, m;
    cin>>n>>m;
    vector<vector<int>> arr(n,vector<int>(m));
    for(int i = 0;i<n;i++){
        for(int j = 0;j<m;j++){
            cin>>arr[i][j];
        }
    }
    unordered_map<int,vector<int>> mp;

    vector<vector<int>>seen(n,vector<int>(m,0));
    queue<int>q;
    while(!q.empty()){
        int x = q.front();
        seen[x]  = seen[x] + 1;
        q.pop();
        for(auto it: mp[x]){
            q.push(it);
        }

    }
}
int main(){
    int t;
    cin>>t;
    while(t--)
    {
        solve();
    }
}