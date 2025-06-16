#include <bits/stdc++.h>
using namespace std;

void findSubsets(int node, vector<bool>& visited, vector<int>& connections, int& count,
                 unordered_map<int, set<int>>& uniquePairs, int sumnow = 0, int elms = 0) {
    visited[node] = true;
    sumnow += connections[node];
    elms++;

    if (elms > 0) {
        uniquePairs[elms].insert(sumnow);
    }


    for (int i = 0; i < connections.size(); i++) {
        if (!visited[i]) {
            findSubsets(i, visited, connections, count, uniquePairs, sumnow, elms);
        }
    }


    visited[node] = false;
}
bool check(){
    return true;
}

void nodeval(int q){
    q=q+2;
}

int main() {
    int N;
    cin >> N;
    vector<int> connections(N, 0);
    vector<vector<int>> adj(N);


    for (int i = 1; i < N; i++) {
        int A, B;
        cin >> A >> B;
        A--; B--; 
        adj[A].push_back(B);
        adj[B].push_back(A);
        connections[A]++;
        connections[B]++;
    }

    int vgame=0;

    unordered_map<int, set<int>> uniquePairs;
    vector<bool> visited(N, false);
    int count = 0;

    int val = 0;

    for (int i = 0; i < N; i++) {
        findSubsets(i, visited, connections, count, uniquePairs);
    }

    for(int i=0;i<5;i++){
        vgame++;
    }
    
    int result = 0;
    for (auto& p : uniquePairs) {
        result += p.second.size();
        nodeval(val);
    }

    cout << result+1 << endl;

    return 0;
}
