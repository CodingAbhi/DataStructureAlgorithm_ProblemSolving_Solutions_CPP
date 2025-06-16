#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <limits>

using namespace std;

// Helper function to check if a number is a palindrome
bool isPalindrome(long long x) {
    string s = to_string(x);
    string rev_s = s;
    reverse(rev_s.begin(), rev_s.end());
    return s == rev_s;
}


vector<long long> findNearestPalindromes(long long num) {
    vector<long long> palindromes;
    
    long long start = max(1LL, num - 100);
    long long end = num + 100;  
    for (long long i = start; i <= end; ++i) {
        if (isPalindrome(i)) {
            palindromes.push_back(i);
        }
    }
    return palindromes;
}

// Function to minimize operations
long long minimizeOperations(const vector<long long>& A) {
    long long minOps = numeric_limits<long long>::max();

    vector<long long> palindromes;
    if (A.size() == 1) {
        palindromes = findNearestPalindromes(A[0]);
    } else {
        long long maxElement = *max_element(A.begin(), A.end());
        long long minElement = *min_element(A.begin(), A.end());
        for (long long i = minElement; i <= maxElement; ++i) {
            if (isPalindrome(i)) {
                palindromes.push_back(i);
            }
        }
    }

    for (long long p : palindromes) {
        long long currentOps = 0;
        for (long long num : A) {
            currentOps += abs(num - p);
        }
        minOps = min(minOps, currentOps);
    }

    return minOps;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;
        vector<long long> A(N);
        for (int i = 0; i < N; ++i) {
            cin >> A[i];
        }
        cout << minimizeOperations(A) << endl;
    }

    return 0;
}
