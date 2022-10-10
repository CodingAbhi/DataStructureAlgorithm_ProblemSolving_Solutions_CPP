#include <iostream>
using namespace std;
int main()
{
    int n;
    cin >> n;
    int i = 1;
    while (i <= n)
    {
        // int k=i-1;
        int j = 1;
        while (j <= i)
        {
            cout << i + j - 1;
            // k++;
            j++;
            break;
            // while(j<=i){
            //   cout<<i+j-1;
            //}
        }

        cout << endl;
        i++;
    }
}
