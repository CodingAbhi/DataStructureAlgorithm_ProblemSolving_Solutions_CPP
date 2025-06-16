#include <bits/stdc++.h>
using namespace std;
#define int long long
const int mod = 998244353;

void solve() {
    int n;
    cin >> n;
    vector<int> p(n), q(n);
    for (int &x : p) cin >> x;
    for (int &x : q) cin >> x;

    // Precompute powers of 2 up to max element in p or q
    vector<int> twospwer(61);  // Since 1LL << 60 is more than 1e18
    for (int i = 0; i < 61; i++) {
        twospwer[i] = (1LL << i) % mod;
    }

    vector<int> res(n);
    int maxP = -1, maxQ = -1;
    for (int i = 0; i < n; i++) {
        maxP = max(maxP, p[i]);
        maxQ = max(maxQ, q[i]);
        res[i] = (twospwer[maxP] + twospwer[maxQ]) % mod;
    }

    for (int x : res) cout << x << " ";
    cout << '\n';
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
