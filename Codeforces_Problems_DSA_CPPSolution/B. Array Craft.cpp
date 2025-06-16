bool doesAliceWin(string s) {
 int cnt=0;
for(int i=0; i<s.length(); i++){
if(s[i]=='a's[i]=='e's[i]=='i's[i]=='o's[i]=='u'){
 cnt++;
}
}
if(cnt==0) return false;
int ans = 0;while(cnt>0){
int odd=0;
while(odd<cnt && odd%2!=0){
 odd++; 
 }
 cnt = cnt-odd;
 int even=0;
 while(even<cnt && even%2==0){
 even++;
 }
 cnt = cnt-even;
 }
 if(cnt%2==0) return true;
 else return false;
  }