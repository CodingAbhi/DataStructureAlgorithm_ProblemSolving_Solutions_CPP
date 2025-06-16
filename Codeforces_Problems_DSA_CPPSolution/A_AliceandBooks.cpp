#include <bits/stdc++.h>
using namespace std;

int fibonacci(int n) {
     
      int prev1 = 0;
       int prev2 = 1;

        int res;
         for (int i = 2; i <= n; i++) {

              res = prev1 + prev2;
              cout<<res<<" ";
               prev1 = prev2;
                prev2 = res;
         }
        cout<<endl;
          return res;
}

int main() {
     int n;
      n = 10;
       
        cout << fibonacci(n);
}