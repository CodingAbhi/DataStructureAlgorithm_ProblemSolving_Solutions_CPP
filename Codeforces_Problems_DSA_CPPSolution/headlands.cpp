#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using namespace std;

struct LogEntry {
    int id;
    int timestamp;
    vector<pair<string, string>> files;
};

struct Query {
    int start_timestamp;
    int end_timestamp;
    string file_path;
    string opaque_identifier;
};


class DSU {
public:
    unordered_map<string, string> parent;
    unordered_map<string, int> rank;

    string find(const string& x) {
        if (parent.find(x) == parent.end()) {
            parent[x] = x;
            rank[x] = 1;
        }
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void unite(const string& x, const string& y) {
        string rootX = find(x);
        string rootY = find(y);

        if (rootX != rootY) {
            if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }
};

bool parseLogEntry(const string& line, LogEntry& log) {
    istringstream iss(line);
    string token;
    if (!(iss >> token) || token != "id") return false;
    if (!(iss >> log.id)) return false;
    if (!(iss >> token) || token != "timestamp") return false;
    if (!(iss >> log.timestamp)) return false;
    log.files.clear();
    string path, opaque;
    while (iss >> path >> opaque) {
        log.files.push_back({path, opaque});
    }
    return !log.files.empty();
}

bool parseQuery(const string& line, Query& query) {
    istringstream iss(line);
    if (iss >> query.start_timestamp >> query.end_timestamp >> query.file_path >> query.opaque_identifier) {
        return true;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    cin.ignore();
    vector<LogEntry> logs;
    for (int i = 0; i < N; ++i) {
        string line;
        getline(cin, line);
        LogEntry log;
        if (parseLogEntry(line, log)) {
            logs.push_back(log);
        }
    }

    DSU dsu;
    unordered_map<string, unordered_set<string>> fileToOpaqueMap;
    bool isAmbiguous = false;

    for (const auto& log : logs) {
        for (const auto& file : log.files) {
            string filePath = file.first;
            string opaque = file.second;

            if (fileToOpaqueMap[filePath].count(opaque) == 0) {
                fileToOpaqueMap[filePath].insert(opaque);
            } else {
                isAmbiguous = true;
                break;
            }
        }
        if (isAmbiguous) break;
    }

    if (isAmbiguous) {
        cout << "AMBIGUOUS INPUT!" << endl;
        return 0;
    }

    unordered_map<string, vector<string>> fileToLogMap;

    for (const auto& log : logs) {
        for (const auto& file : log.files) {
            string filePath = file.first + "." + file.second;
            string logIdStr = to_string(log.id);
            if (!fileToLogMap[filePath].empty()) {
                dsu.unite(fileToLogMap[filePath][0], logIdStr);
            }
            fileToLogMap[filePath].push_back(logIdStr);
        }
    }

    unordered_map<string, int> commitToLog;
    for (const auto& log : logs) {
        string root = dsu.find(to_string(log.id));
        int rootId = stoi(root);
        if (commitToLog.find(root) == commitToLog.end()) {
            commitToLog[root] = log.id;
        } else {
            commitToLog[root] = min(commitToLog[root], log.id);
        }
    }

    int R;
    cin >> R;
    cin.ignore();
    vector<Query> queries(R);
    for (int i = 0; i < R; ++i) {
        string line;
        getline(cin, line);
        if (parseQuery(line, queries[i])) {
            // done
        }
    }

    for (const auto& query : queries) {
        vector<int> result;
        for (const auto& log : logs) {
            if (log.timestamp >= query.start_timestamp && log.timestamp <= query.end_timestamp) {
                for (const auto& file : log.files) {
                    if (file.first == query.file_path && file.second == query.opaque_identifier) {
                        result.push_back(log.id);
                        break;
                    }
                }
            }
        }
        sort(result.begin(), result.end(), [&logs](int a, int b) {
            if (logs[a].timestamp != logs[b].timestamp) return logs[a].timestamp < logs[b].timestamp;
            return logs[a].id < logs[b].id;
        });

        for (int id : result) {
            cout << id << " ";
        }
        cout << "\n";
    }

    return 0;
}
