int findmaxPath(int root, int &ans, vector<int> &parent, vector<int> &values, vector<bool> &computed){
    if(computed[root]) return values[root];
    if(parent[root]==-1) {
         computed[root]=true;
    }
    else{
        computed[root]=true;
        int parentpath = findmaxPath(parent[root], ans, parent, values, computed);
        values[root] = max(parentpath+values[root], values[root]);
    }
    ans = max(ans, values[root]);
    return values[root];
}

int bestSumDownwardTreePath(vector<int> parent, vector<int> values) {
    int n=parent.size();
    int ans = values[0];
    vector<bool> computed(n, false);
    for(int i=0; i<n; i++){
        if(computed[i]) continue;
        findmaxPath(i, ans, parent, values, computed);
    }
    return ans;
}

//Bny best sum any tree path