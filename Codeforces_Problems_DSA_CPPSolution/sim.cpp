#include <iostream>
using namespace std;
#include <queue>
#include <tuple>
#include <unordered_set>
#include <string>


string hashCandyState(int a, int b, int c) {
    return to_string(a) + '#' + to_string(b) + '#' + to_string(c);
}

int minMoves(int a, int b, int c) {
    queue<tuple<int, int, int, int>> q; // queue to store state and moves
    unordered_set<string> visited; // to avoid revisiting the same state

    // initial enqueue
    q.push({a, b, c, 0});
    visited.insert(hashCandyState(a, b, c));

    while (!q.empty()) {
        auto [ca, cb, cc, moves] = q.front();
        q.pop();

        // If all candies are of one type
        if (ca == 0 && cb == 0 && cc > 0) return moves;
        if (ca == 0 && cc == 0 && cb > 0) return moves;
        if (cb == 0 && cc == 0 && ca > 0) return moves;

        // Generate all possible next states
        if (ca > 0 && cb > 0) { // Convert a and b to c
            int na = ca - 1, nb = cb - 1, nc = cc + 2;
            string stateHash = hashCandyState(na, nb, nc);
            if (visited.find(stateHash) == visited.end()) {
                q.push({na, nb, nc, moves + 1});
                visited.insert(stateHash);
            }
        }
        if (ca > 0 && cc > 0) { // Convert a and c to b
            int na = ca - 1, nc = cc - 1, nb = cb + 2;
            string stateHash = hashCandyState(na, nb, nc);
            if (visited.find(stateHash) == visited.end()) {
                q.push({na, nb, nc, moves + 1});
                visited.insert(stateHash);
            }
        }
        if (cb > 0 && cc > 0) { // Convert b and c to a
            int nb = cb - 1, nc = cc - 1, na = ca + 2;
            string stateHash = hashCandyState(na, nb, nc);
            if (visited.find(stateHash) == visited.end()) {
                q.push({na, nb, nc, moves + 1});
                visited.insert(stateHash);
            }
        }
    }

    return -1; // If no solution found
}

int main() {
    int a, b, c;
    cin >> a >> b >> c;

    cout << minMoves(a, b, c) << endl;

    return 0;
}
