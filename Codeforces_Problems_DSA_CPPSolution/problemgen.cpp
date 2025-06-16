#include<bits/stdc++.h>
using namespace std;

void solve(){
int n,f,k;
// int ans=0;
cin>>n>>f>>k;
f--;

int arr[n]={0};
for(int i=0;i<n;i++){
    cin>>arr[i];
}
int favnum=arr[f];
sort(arr,arr+n);
reverse(arr,arr+n);
// for(int i=0;i<n;i++)
// {
//     cout<<arr[i]<<endl;
// }
int minind;
int maxind;
for(int i=0;i<n;i++){
    if(arr[i]==favnum){
        minind=i;
        break;
    }
}
for(int i=0;i<n;i++){
    if(arr[i]==favnum){
        maxind=i;

    }
}
// cout<<minind<<" lele" <<maxind<<"comp krle with "<<k-1<<endl;
if(maxind<=k-1){
    cout<<"YES"<<endl;
}
else if(minind>k-1)
{
    cout<<"NO"<<endl;
}else
{
    cout<<"MAYBE"<<endl;
}
// return ans;


}

int main(){
int t;
cin>>t;
while(t){
    
    solve();
    t--;
}
// return ans;
return 0;


}
