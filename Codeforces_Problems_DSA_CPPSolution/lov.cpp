#include <bits/stdc++.h>
using namespace std;

class UnionFind
{
    vector<int> parent, rank;
    int time, count;

public:
    UnionFind(int N) : parent(N), rank(N), count(N)
    {
        time = 0;
        for (int i = 0; i < N; i++)
        {
            parent[i] = i;
            rank[i] = 1;
        }
    }

    int find(int node)
    {
        if (node == parent[node])
            return node;
        return parent[node] = find(parent[node]);
    }

    void performUnion(int u, int v, int updatedTime)
    {
        if (count == 1)
            return;
        int rootX = find(u);
        int rootY = find(v);
        if (rootX != rootY)
        {
            if (rank[rootX] < rank[rootY])
            {
                parent[rootX] = rootY;
            }
            else if (rank[rootX] > rank[rootY])
            {
                parent[rootY] = rootX;
            }
            else
            {
                parent[rootX] = rootY;
                rank[rootY] += 1;
            }
            time = updatedTime;
            count--;
        }
    }

    int getCount()
    {
        return count;
    }

    int getTime()
    {
        return time;
    }
};

bool cmp(vector<int> &A, vector<int> &B)
{
    return A[2] <= B[2];
}

int earliestTime(int N, vector<vector<int>> &arr)
{
    UnionFind dsu(N);
    sort(arr.begin(), arr.end(), cmp);
    for (int i = 0; i < arr.size(); i++)
    {
        dsu.performUnion(arr[i][0], arr[i][1], arr[i][2]);
        if (dsu.getCount() == 1)
            return dsu.getTime();
    }
    return -1;
}

int main()
{
    int N = 4;
    vector<vector<int>> arr = {{0, 1, 2}, {1, 2, 3}, {2, 3, 4}};
    cout << earliestTime(N, arr) << endl;
    return 0;
}
