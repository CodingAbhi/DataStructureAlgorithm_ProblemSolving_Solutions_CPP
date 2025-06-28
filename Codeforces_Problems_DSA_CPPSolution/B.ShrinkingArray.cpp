#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void solve(){
    int n;
    cin>>n;
    vector<int> arr(n);
    for(int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    int ans = -1;
    for(int i = 2;i<n;i++){
        if(min(arr[i-1],arr[i-2])<=arr[i] && arr[i]<=max(arr[i-1],arr[i-2])){
            ans =1;
        }
    }
    for(int i = 0;i<n-2;i++){
        if(min(arr[i+1],arr[i+2])<=arr[i] && arr[i]<=max(arr[i+1],arr[i+2])){
            ans = 1;
        }
    }
    for(int i = 1;i<n;i++){
        if(abs(arr[i] - arr[i-1]) <= 1) {
            ans = 0;
        }
    }
    cout<<ans<<endl;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
       solve();
    }
    return 0;
}
