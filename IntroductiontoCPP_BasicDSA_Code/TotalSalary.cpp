#include<bits/stdc++.h>
using namespace std;
int main(){
    int basic;
    char grade;
    double totalsalary;
    int allow;
    cin>>basic>>grade;
    if(grade == 'A'){
        allow=1700;
    }else if (grade=='B'){allow=1500;}
    else{allow=1300;
    }
    totalsalary = basic + 0.2*basic + 0.5*basic + allow - 0.11*basic;
    cout<<fixed<<setprecision(0)<<totalsalary<<endl;
        
}