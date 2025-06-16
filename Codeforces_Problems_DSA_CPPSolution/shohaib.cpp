#include <iostream>
#include <vector>

using namespace std;

bool isLocalMaximum(const vector<vector<int>>& matrix, int i, int j) {
    int n = matrix.size();
    int m = matrix[0].size();
    int value = matrix[i][j];

    // Check above
    if (i > 0 && matrix[i-1][j] >= value) return false;

    // Check below
    if (i < n-1 && matrix[i+1][j] >= value) return false;

    // Check left
    if (j > 0 && matrix[i][j-1] >= value) return false;

    // Check right
    if (j < m-1 && matrix[i][j+1] >= value) return false;

    return true;
}

void stabilizeMatrix(vector<vector<int>>& matrix) {
    int n = matrix.size();
    int m = matrix[0].size();
    bool changed;

    do {
        changed = false;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (isLocalMaximum(matrix, i, j)) {
                    matrix[i][j]--;
                    changed = true;
                }
            }
        }
    } while (changed);
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        vector<vector<int>> matrix(n, vector<int>(m));

        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                cin >> matrix[i][j];

        stabilizeMatrix(matrix);

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
    }

    return 0;
}
