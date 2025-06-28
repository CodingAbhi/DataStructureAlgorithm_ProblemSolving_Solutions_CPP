#include<bits/stdc++.h>
using namespace std;

void solve(){
    int a,b;
    cin>>a>>b;
    int ko,kt;
    cin>>ko>>kt;
    int qo,qt;
    cin>>qo>>qt;
    set<pair<int,int>> com;
    vector<pair<int,int>> knightdir = {{a,b},{a,-b},{b,-a},{b,a},{-a,b},{-a,-b},{-b,-a},{-b,a}};
    map<pair<int,int>,char> mp;
    for(int i = 0;i<knightdir.size();i++){
      int x = knightdir[i].first+ko;
      int y = knightdir[i].second+kt;
      int p = knightdir[i].first+qo;
        int q = knightdir[i].second+qt;
    if(mp[{x,y}] == 'q'){
        com.insert({x,y});
        continue;
      }
      if(mp[{p,q}]=='k'){
        com.insert({p,q});
        continue;
      }
      mp[{x,y}] = 'k';
      mp[{p,q}] = 'q';

    }
    cout<<com.size()<<endl;

}

int main(){
    int t;
    cin >> t;
    while(t--) {
        solve();
    }
}