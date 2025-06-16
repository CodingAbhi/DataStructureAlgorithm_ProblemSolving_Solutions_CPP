#include <iostream>
using namespace std;

const int MOD = 1000000007; 

long long modExp(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) { 
            result = (result * base) % mod;
        }
        exp = exp >> 1; 
        base = (base * base) % mod; 
    }
    return result;
}

int main() {
    int n;
    cout << "Enter the number of vertices: ";
    cin >> n;

    long long numEdges = (long long)n * (n - 1) / 2;

    long long numGraphs = modExp(2, numEdges, MOD);

    cout << "Number of distinct graphs is: " << numGraphs << endl;

    return 0;
}
