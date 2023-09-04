#include <iostream>
#include <cmath>
using namespace std;

// Function to calculate the Nth character of the alphabet string
char getNthChar(long long N)
{
    // calculate the number of characters in the longest repeated substring
    long long len = 1, sum = 26;
    while (N > sum)
    {
        N -= sum;
        sum *= 26;
        len++;
    }
    // calculate the index of the Nth occurrence of the current letter
    long long idx = (N - 1) / (len * pow(26, len - 1));
    // calculate the ASCII value of the Nth character
    int ascii_val = 'A' + (idx % 26);
    // calculate the position of the Nth character in the current repeated substring
    long long pos = len - ((N - 1) % (len * static_cast<long long>(pow(26, len - 1)))) / idx;
    return static_cast<char>(ascii_val + pos - 1);
}

int main()
{
    int T;
    cin >> T;
    for (int t = 1; t <= T; t++)
    {
        long long N;
        cin >> N;
        char nth_char = getNthChar(N);
        cout << "Case #" << t << ": " << nth_char << endl;
    }
    return 0;
}
