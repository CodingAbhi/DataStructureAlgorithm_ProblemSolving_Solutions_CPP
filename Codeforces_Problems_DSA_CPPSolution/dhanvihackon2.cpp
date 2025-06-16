#include <iostream>
#include <vector>
#include <map>
using namespace std;

// Function to check if a window is a valid permutation of 1..N
bool isValidPermutation(const map<int, int>& freq, int N) {
    if ((int)freq.size() != N) return false;
    for (map<int, int>::const_iterator it = freq.begin(); it != freq.end(); ++it) {
        if (it->second != 1) return false;
    }
    return true;
}

int main() {
    int N;
    long long M;
    cin >> N >> M;
    vector<long long> B(N);
    for (int i = 0; i < N; ++i) {
        cin >> B[i];
    }

    // Build the large array A from B
    vector<int> A;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < B[i]; ++j) {
            A.push_back(i + 1);
        }
    }

    // Add M elements greedily to balance the frequency of all numbers
    while (M > 0) {
        int minIndex = 0;
        for (int i = 1; i < N; ++i) {
            if (B[i] < B[minIndex]) minIndex = i;
        }
        A.push_back(minIndex + 1);
        B[minIndex]++;
        M--;
    }

    // Count number of subarrays of length N that are permutations of 1..N
    int count = 0;
    map<int, int> freq;
    for (int i = 0; i < A.size(); ++i) {
        freq[A[i]]++;
        if (i >= N) {
            freq[A[i - N]]--;
            if (freq[A[i - N]] == 0) {
                freq.erase(A[i - N]);
            }
        }
        if (i >= N - 1 && isValidPermutation(freq, N)) {
            count++;
        }
    }

    cout << count << endl;
    return 0;
}
