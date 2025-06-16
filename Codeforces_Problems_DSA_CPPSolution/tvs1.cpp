#include <bits/stdc++.h>
using namespace std;
struct Result {
    int output1;
    int output2;
};
Result profitDevelopment(int input1, int input2, int input3, int input4[]) {

    vector<int> a(input4, input4 + input1);

    Result res;
    
    int l = input1 / input2;
    vector<pair<int, int>> ans;
    vector<pair<vector<int>, int>> c;

    for (int i = 0; i < l; i++) {
        int si = i * input2;
        vector<int> v(a.begin() + si, a.begin() + si + input2);
        sort(v.begin(), v.end());
        c.push_back({v, i + 1});
    }

    sort(c.begin(), c.end());

    for (auto& i : c) {
        for (auto& r : i.first) {
            ans.push_back({r, i.second});
        }
    }

    if (input3 - 1 < ans.size()) {
        res.output1 = ans[input3 - 1].second;
        res.output2 = ans[input3 - 1].first;
    } else {
        throw "Index out of range";
    }

    return res;
}

int main() {
    int n, s, m;
    cin >> n >> s >> m;
    int a[n];
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    try {
        Result r = profitDevelopment(n, s, m, a);
        cout << r.output1 << " " << r.output2 << endl;
    } catch (const char* msg) {
        cerr << msg << endl;
    }

    return 0;
}