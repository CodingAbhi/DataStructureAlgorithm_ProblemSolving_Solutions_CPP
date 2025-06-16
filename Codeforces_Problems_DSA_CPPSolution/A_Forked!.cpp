#include <bits/stdc++.h>
using namespace std;
 
void solve() {
    long double a = 36.102143;
    long double b = -115.174494;
    cout<<fixed<<setprecision(6)<<a<<" "<<b<<endl;
    }
 
int main() {
    ios::sync_with_stdio(false); 
    cin.tie(nullptr);
    solve();
    return 0;
}


def getMinimumTime(processSize, capacity):
    processSize.sort()
    m = len(capacity)
    n = len(processSize)

    
    result = 0
    left = 0
    
    capacity.sort()
    right = n

    while left <= right:
        pos = n - 1
        mid = (left + right) // 2

        for i in range(m - 1, -1, -1):
            count = mid
            while pos >= 0 and count > 0:
                if processSize[pos] <= capacity[i]:
                    count -= 1
                    pos -= 1
                else:
                    break

        if pos < 0:
            right = mid - 1
            result = mid
        else:
            left = mid + 1

    return result * 2 - 1




def countVisibleTowers(height):
    n = len(height)
    ans = [0] * n

    def calc(height):
        st = []
        for i in range(n):
            ans[i] += len(st)
            while len(st) > 0 and height[st[-1]] <= height[i]:
                st.pop()
            st.append(i)

    calc(height)

    height.reverse()
    ans.reverse()
    calc(height)

    ans.reverse()
    return ans
