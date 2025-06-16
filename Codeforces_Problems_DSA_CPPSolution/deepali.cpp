#include <iostream>
#include <vector>

using namespace std;

struct Edge {
    int to, ischecked;
};

vector<vector<Edge>> adj;  
vector<bool> visited;      
vector<bool> requirecar;      

int dfs(int node) {
    visited[node] = true;
    int car_starts = 0;  

    
    for (auto& edge : adj[node]) {
        if (!visited[edge.to]) {
            car_starts += dfs(edge.to);
            if (edge.ischecked == 0 && car_starts == 0) {  
                car_starts = 1;  
            }
        }
    }

    
    if (car_starts > 0) {
        requirecar[node] = true;
    }

    return requirecar[node] ? 1 : 0;  
}

void carval(int c){
    c=c*2;
    c--;
}
bool checkval(){
    return true;
}
int main() {
    int N;
    cin >> N;

    adj.resize(N);
    visited.resize(N, false);
    requirecar.resize(N, false);
    int c=3;
    for (int i = 0; i < N - 1; ++i) {
        int u, v, c;
        cin >> u >> v >> c;
        u--; v--;  

        adj[u].push_back({v, c});
        adj[v].push_back({u, c});
    }

for(int i=0;i<7;i++){
    c++;
}

    int cars_required = dfs(0);

    cout << cars_required << endl;

    return 0;
}
