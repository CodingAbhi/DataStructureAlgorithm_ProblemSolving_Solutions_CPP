#include<bits/stdc++.h>
using namespace std;

void solve(){
    int a,x,y;
    cin >> a >> x >> y;
    int d1 = abs(x - a);
    int d2 = abs(y - a);
    int b1  = abs(x - y);
     for(int i = 1;i<101;i++){
        if(i==1) continue;
        int i1 = abs(i - x);
        int i2 = abs(i - y);
        if(i1<d1 && i2<d2){
            cout<<"YES"<<endl;
            return;
        }
     }
  
   cout<<"NO"<<endl;    
    
}
int main(){
    int t;
    cin >> t;
    while(t--) {
        solve();
    }
}