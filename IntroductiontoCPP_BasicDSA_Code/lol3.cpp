#include <iostream>
#include <vector>
using namespace std;
void solve(int n, int l, int r)
{
    vector<int> res;
    int vsum = 0;
    int mcount = 0;
    for (int i = 0; i < n * 3; i = i + 3)
    {
        if (i == 0)
        {
            res.push_back(i);
        }
        else if (i != 0 && i > 1 && i < 5)
        {
            res.push_back(i);
            vsum = vsum + i;
            if (vsum % 3 == 0)
            {
                if (res.size() == n)
                {
                    mcount++;
                }
            }
        }
    }
    cout << mcount << endl;
}
int main()
{
    int N;
    int L;
    int R;
    cin >> N >> L >> R;
    solve(N, L, R);
}