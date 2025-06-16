#include<bits/stdc++.h>
using namespace std;
int main(){


    int n;
    cin>>n;
    vector<vector<pair<int,int>>> adj(n+1);
    int edges;
    cin>>edges;
    for(int i=1; i<=edges; i++){
        int u,v,bus;
        cin>>u>>v>>bus;
        adj[u].push_back({v, bus});
    }
    if(n == 1){ //if src equals destination
        cout<<0<<endl;
        return 0;
    }
    else{
        int ans = INT_MAX;
        map<pair<int,int>, int> mp; //current node with current bus and distance travelled
        priority_queue<pair<int, pair<int,int>>, vector<pair<int, pair<int,int>>>, greater<pair<int, pair<int,int>>>> pq; //dist with node and busnumber
        for(auto it : adj[0]){
            pq.push({0, {0, it.second}});
            mp[{0, it.second}] = 0;
        }
        while(!pq.empty()){
            auto node = pq.top();
            auto d = pq.top().first;
            auto pr = pq.top().second;
            pq.pop();
            if(d != mp[pr])
                continue;
            if(pr.first == n-1){
                ans = min(ans, d);
            }
            for(auto it : adj[pr.first]){
                int wt = 1 + (pr.second != it.second);
                if(!mp.count(it) || (mp.count(it) && d + wt < mp[it])){
                    mp[it] = d + wt;
                    pq.push({mp[it], it});
                }
            }
        }
        cout<<(ans == INT_MAX ? -1 : ans)<<endl;
    }
    return 0;
}

