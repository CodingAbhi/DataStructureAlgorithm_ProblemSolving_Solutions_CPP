#include <bits/stdc++.h>
using namespace std;

int main()
{
    int t;
    cin >> t;
    for (int i = 1; i <= t; i++)
    {
        int n;
        cin >> n;
        vector<long long> a(n + 1);
        for (int j = 1; j <= n; j++)
        {
            cin >> a[j];
        }
        int la, ra, lb, rb;
        cin >> la >> ra >> lb >> rb;

        vector<long long> prefix_sum(n + 1);
        for (int j = 1; j <= n; j++)
        {
            prefix_sum[j] = prefix_sum[j - 1] + a[j];
        }

        long long alice_max = 0;
        long long bob_max = 0;

        // Alice's turn
        for (int j = la; j <= ra; j++)
        {
            long long alice = prefix_sum[j] - prefix_sum[la - 1] +
                              prefix_sum[ra] - prefix_sum[j];
            long long bob = max(prefix_sum[lb - 1], prefix_sum[rb] - prefix_sum[j]);
            alice_max = max(alice_max, alice - bob);
        }

        // Bob's turn
        for (int j = lb; j <= rb; j++)
        {
            long long bob = prefix_sum[j] - prefix_sum[lb - 1] +
                            prefix_sum[rb] - prefix_sum[j];
            long long alice = max(prefix_sum[la - 1], prefix_sum[ra] - prefix_sum[j]);
            bob_max = max(bob_max, bob - alice);
        }

        long long ans = prefix_sum[n] - bob_max;
        cout << "Case #" << i << ": " << ans << endl;
    }
    return 0;
}
