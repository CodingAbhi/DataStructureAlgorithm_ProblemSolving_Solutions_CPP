#include <iostream>
#include <string>
using namespace std;

bool isVowel(char c) {
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

string solveProblem(int n, const string& a, const string& b) {
    string merged_string;
    merged_string.reserve(2 * n);  

    for (int i = 0; i < n; ++i) {
        merged_string += a[i];
        merged_string += b[i];
    }

    int vowel_count = 0;
    for (char c : merged_string) {
        if (isVowel(c)) {
            ++vowel_count;
        }
    }

    int len = 2 * n;
    int k = vowel_count % len;  


    if (k == 0) return merged_string;
    return merged_string.substr(len - k) + merged_string.substr(0, len - k);
}

int main() {
    int n;
    string a, b;
    cin >> n >> a >> b;
    
    cout << solveProblem(n, a, b) << endl;
    return 0;
}
