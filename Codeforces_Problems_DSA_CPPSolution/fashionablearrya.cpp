#include<bits/stdc++.h>
using namespace std;


void solve(){
int n;
cin>>n;
vector<int> arr(n,0);
for(int i =0;i<n;i++){
    cin>>arr[i];
}

sort(arr.begin(),arr.end());

int ans =0;
int res = 0;
int j = 0;
int k = n-1;
while((arr[j]+arr[k])%2)
   { k--;
    ans++;
}
k = n-1;
while((arr[j]+arr[k])%2)
   { j++;
    res++;}
cout<<min(ans,res);

}

int main(){
    int t;
    cin>>t;
    while(t--){
        solve();
        cout<<endl;
    }
}