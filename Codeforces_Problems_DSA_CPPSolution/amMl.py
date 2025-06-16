#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

// Function to compute the modular inverse of a under modulo m
long long modinv(long long a, long long m) {
    long long m0 = m, t, q;
    long long x0 = 0, x1 = 1;

    if (m == 1) return 0;

    // Apply extended Euclid Algorithm
    while (a > 1) {
        q = a / m;
        t = m;

        // m is remainder now, process same as Euclid's algo
        m = a % m, a = t;
        t = x0;

        x0 = x1 - q * x0;
        x1 = t;
    }

    // Make x1 positive
    if (x1 < 0) x1 += m0;

    return x1;
}

void solve() {
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        vector<int> values(n);
        long long total_value = 0, special_value = 0;

        for (int i = 0; i < n; ++i) {
            cin >> values[i];
            total_value += values[i];
            if (i < k) special_value += values[i];
        }

        long long p = special_value;
        long long q = total_value;

        if (p == 0) {
            cout << "0" << endl;
            continue;
        }

        long long prob_special = p * modinv(q, MOD) % MOD;
        long long prob_non_special = (q - p) * modinv(q, MOD) % MOD;

        long long expected_alice = p * modinv(q, MOD) % MOD;
        long long expected_bob = (q - p) * modinv(q, MOD) % MOD;

        long long total = (expected_alice * modinv(1 - prob_special + MOD, MOD) + expected_bob * prob_special * modinv((1 - prob_special + MOD) * (1 - prob_special + MOD) % MOD, MOD)) % MOD;

        cout << total << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
