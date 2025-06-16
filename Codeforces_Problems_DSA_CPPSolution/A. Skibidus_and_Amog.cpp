#include <bits/stdc++.h>
#include <string>
using namespace std;

void solve() {
    int n,m;
    cin>>n>>m;
    int a[n];
    int b[m];
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    for(int i = 0;i<m;i++){
        cin>>b[i];
    }
    int k = b[0];
    for(int i = 0;i<n;i++){
        if(k-a[i]<a[i]){
            a[i] = k-a[i];
        }
    }

}

int main() {
    int t;
    cin >> t;
    while (t--) solve();
}
