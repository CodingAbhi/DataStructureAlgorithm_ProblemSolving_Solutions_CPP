#include <iostream>
#include <vector>
using namespace std;

vector<pair<int, int>> findFirstZeros(const vector<vector<int>>& matrix) {
    int n = matrix.size();
    int m = matrix[0].size();
    vector<pair<int, int>> coordinates;

    for (int i = 0; i < n; ++i) {
        int low = 0, high = m - 1;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (matrix[i][mid] == 1) {
                low = mid + 1;
            } else if (mid == 0 || matrix[i][mid - 1] == 1) {
                coordinates.push_back({i, mid});
                break;
            } else {
                high = mid - 1;
            }
        }
    }

    return coordinates;
}

int main() {
    vector<vector<int>> matrix = {
       
        {1, 1, 1, 1, 1, 1}
    };
    vector<pair<int, int>> results = findFirstZeros(matrix);
    pair<int,int> res = {-1,-1};
    int mini = 1e9+7;

    for (const auto& coord : results) {
        // cout << "First 0 at row " << coord.first << ", column " << coord.second << endl;
        if(coord.second<mini){
            res = coord;
        }
    }
    cout<<res.first<<" "<<res.second;

    return 0;
}
