#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

void dfs1(int v, vector<bool>& visited, stack<int>& finishStack, const vector<vector<int>>& adj) {
    visited[v] = true;
    for (int u : adj[v]) {
        if (!visited[u]) {
            dfs1(u, visited, finishStack, adj);
        }
    }
    finishStack.push(v);
}

void dfs2(int v, int sccIndex, vector<bool>& visited, vector<int>& sccId, const vector<vector<int>>& adjRev) {
    visited[v] = true;
    sccId[v] = sccIndex;
    for (int u : adjRev[v]) {
        if (!visited[u]) {
            dfs2(u, sccIndex, visited, sccId, adjRev);
        }
    }
}

int findMinEdgesToAdd(int n, const vector<int>& instructions) {
    vector<vector<int>> adj(n), adjRev(n);
    for (int i = 0; i < n; ++i) {
        int target = instructions[i] - 1; 
        adj[i].push_back(target);
        adjRev[target].push_back(i);
    }

    
    vector<bool> visited(n, false);
    stack<int> finishStack;
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            dfs1(i, visited, finishStack, adj);
        }
    }

    fill(visited.begin(), visited.end(), false);
    vector<int> sccId(n, -1);
    int sccIndex = 0;

    while (!finishStack.empty()) {
        int v = finishStack.top();
        finishStack.pop();
        if (!visited[v]) {
            dfs2(v, sccIndex++, visited, sccId, adjRev);
        }
    }

    
    if (sccIndex == 1) {
        return 0;
    }

    
    vector<int> inDegree(sccIndex, 0), outDegree(sccIndex, 0);
    for (int i = 0; i < n; ++i) {
        for (int j : adj[i]) {
            if (sccId[i] != sccId[j]) {
                outDegree[sccId[i]]++;
                inDegree[sccId[j]]++;
            }
        }
    }

    int countSources = 0, countSinks = 0;
    for (int i = 0; i < sccIndex; ++i) {
        if (inDegree[i] == 0) countSources++;
        if (outDegree[i] == 0) countSinks++;
    }

    
    return max(countSources, countSinks);
}

int main() {
    int n;
    cin >> n;
    vector<int> instructions(n);
    for (int i = 0; i < n; ++i) {
        cin >> instructions[i];
    }

    cout << findMinEdgesToAdd(n, instructions) << endl;
    return 0;
}
