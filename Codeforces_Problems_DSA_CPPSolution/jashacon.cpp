#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int N, M;
    cin >> N >> M;

    vector<vector<int>> packages(N + 1); // packages[from] = list of to's

    for (int i = 0; i < M; ++i) {
        int a, b;
        cin >> a >> b;
        packages[a].push_back(b);
    }

    for (int start = 1; start <= N; ++start) {
        int maxTime = 0;

        for (int from = 1; from <= N; ++from) {
            int count = packages[from].size();
            if (count == 0) continue;

            int distToFrom = (from - start + N) % N;
            int maxDistToDest = 0;

            for (int b : packages[from]) {
                int dist = (b - from + N) % N;
                maxDistToDest = max(maxDistToDest, dist);
            }

            int totalTime = distToFrom + (count - 1) * N + maxDistToDest;
            maxTime = max(maxTime, totalTime);
        }

        cout << maxTime << (start == N ? "\n" : " ");
    }

    return 0;
}
