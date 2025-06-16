#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <map>
#include <sstream>
#include <limits>
#include <algorithm>

using namespace std;

// Function to perform BFS and find shortest distances
vector<int> bfs(int start_node, int num_cities, const vector<vector<int>>& adj) {
    vector<int> dist(num_cities, numeric_limits<int>::max());
    queue<int> q;

    dist[start_node] = 0;
    q.push(start_node);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : adj[u]) {
            if (dist[v] == numeric_limits<int>::max()) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
    return dist;
}

// Main function to solve the problem
int solve(int start_A_idx, int start_B_idx, int start_D_idx, int num_cities, const vector<vector<int>>& adj) {
    vector<int> distA = bfs(start_A_idx, num_cities, adj);
    vector<int> distB = bfs(start_B_idx, num_cities, adj);
    vector<int> distD = bfs(start_D_idx, num_cities, adj);

    int min_total_edges = numeric_limits<int>::max();

    for (int m = 0; m < num_cities; ++m) {
        // Check if city m is reachable from A, B, and D
        if (distA[m] != numeric_limits<int>::max() &&
            distB[m] != numeric_limits<int>::max() &&
            distD[m] != numeric_limits<int>::max()) {
            
            min_total_edges = min(min_total_edges, distA[m] + distB[m] + distD[m]);
        }
    }

    return min_total_edges;
}

int main() {
    // Example input format: "A - F| \ C - E - D| B - G - H"
    string line;
    getline(cin, line);

    char start_A_char, start_B_char, start_D_char;
    cin >> start_A_char >> start_B_char >> start_D_char;

    // Clear the rest of the line after reading chars
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    map<char, int> char_to_int;
    vector<char> int_to_char;
    vector<pair<int, int>> edges; // Store edges as int pairs

    // Parse cities and edges from the line
    stringstream ss(line);
    string segment;
    char city_char;
    vector<char> current_path_cities;

    for (char c : line) {
        if (isupper(c)) {
            if (char_to_int.find(c) == char_to_int.end()) {
                char_to_int[c] = int_to_char.size();
                int_to_char.push_back(c);
            }
        }
    }
    
    // Build edges based on segments and hyphens
    stringstream edge_ss(line);
    string path_segment;
    
    while(getline(edge_ss, path_segment, '|')) {
        stringstream segment_ss(path_segment);
        string city_name;
        vector<int> current_segment_nodes;
        
        while(getline(segment_ss, city_name, '-')) {
             // Trim whitespace
            city_name.erase(remove_if(city_name.begin(), city_name.end(), ::isspace), city_name.end());
            if (!city_name.empty()) {
                current_segment_nodes.push_back(char_to_int[city_name[0]]);
            }
        }

        for(size_t i = 0; i + 1 < current_segment_nodes.size(); ++i) {
            edges.push_back({current_segment_nodes[i], current_segment_nodes[i+1]});
             edges.push_back({current_segment_nodes[i+1], current_segment_nodes[i]}); // Undirected
        }
    }


    int num_cities = int_to_char.size();
    vector<vector<int>> adj(num_cities);

    for (const auto& edge : edges) {
        adj[edge.first].push_back(edge.second);
    }
    
     // Remove duplicate edges in adjacency list if any (not strictly needed for correctness in unweighted BFS, but good practice)
    for(int i=0; i<num_cities; ++i) {
        sort(adj[i].begin(), adj[i].end());
        adj[i].erase(unique(adj[i].begin(), adj[i].end()), adj[i].end());
    }


    int start_A_idx = char_to_int[start_A_char];
    int start_B_idx = char_to_int[start_B_char];
    int start_D_idx = char_to_int[start_D_char];

    int result = solve(start_A_idx, start_B_idx, start_D_idx, num_cities, adj);

    cout << result << endl;

    return 0;
}