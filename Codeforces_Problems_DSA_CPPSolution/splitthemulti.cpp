#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e9+7;

int solve(int f, int k){
    if( f == 0) return 0;
    if( f == 1) return 0;
    if( f<=k) return 1;
    int t = 0;
    
    if( k*k >= f){
        int z = f/k;
        int x = f%k;
            t = 1 + z + solve(x, k);
        
    }
    else{
        int z = f/k;
        int x = f%k;
        t = 1 + (k-1)*solve(z, k) + solve(z+x, k);
    }
    
    return t;
}

int main() {
	int t=0;
cin >> t;
while(t--){
	    int n, k;
	    cin >> n >> k;
	    if( n == 1) cout << 0 << endl;
	    else if( n == 2) cout << 1 << endl;
	    else{
	        
	        cout << solve(n, k) << endl;
	    }
}
	return 0;
}