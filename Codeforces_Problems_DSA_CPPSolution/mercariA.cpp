#include <bits/stdc++.h>
using namespace std;

void dfs(int node, vector<int>& visited, vector<int>& frequencies, vector<int>& maxDepth, vector<vector<int>>& graph, int& longestPath) {
    visited[node] = 1;  
    for (int child : graph[node]) {
        if (!visited[child]) {

            if (abs(frequencies[node] - frequencies[child]) <= 1) {
                maxDepth[child] = maxDepth[node] + 1;  
                dfs(child, visited, frequencies, maxDepth, graph, longestPath);
            }
        }
    }
    longestPath = max(longestPath, maxDepth[node]);  
}

int calculateMax(int network_nodes, vector<int> network_from, vector<int> network_to, vector<int> frequency) {
    vector<vector<int>> graph(network_nodes + 1);
    vector<int> maxDepth(network_nodes + 1, 0);
    vector<int> visited(network_nodes + 1, 0);
    int longestPath = 0;


    for (int i = 0; i < network_from.size(); ++i) {
        graph[network_from[i]].push_back(network_to[i]);
        graph[network_to[i]].push_back(network_from[i]);
    }


    for (int i = 1; i <= network_nodes; ++i) {
        if (!visited[i]) {  
            dfs(i, visited, frequency, maxDepth, graph, longestPath);
        }
    }

    return longestPath;
}

int main() {
    int network_nodes, edges;
    cin >> network_nodes >> edges;
    
    vector<int> network_from(edges), network_to(edges);
    for (int i = 0; i < edges; ++i) {
        cin >> network_from[i] >> network_to[i];
    }
    
    vector<int> frequency(network_nodes);
    for (int i = 0; i < network_nodes; ++i) {
        cin >> frequency[i];
    }
    
    cout << calculateMax(network_nodes, network_from, network_to, frequency) << endl;
    
    return 0;
}
