#include <iostream>
#include <string> 
using namespace std;

#define int long long

int32_t main() {
    int test_cases;
    cin >> test_cases;
    while (test_cases--) {
        int a, b, c;
        cin >> a >> b >> c;
        string instructions;
        cin >> instructions;

        int current_position = b - 1;
        int wasted_moves = 0, failed_operations = 0;

        for (char ch : instructions) {
            if (ch == 'L') {
                current_position = b;
            } else if (ch == 'W') {
                if (current_position <= 0) {
                    wasted_moves++;
                }
            } else {
                if (current_position <= 0) {
                    failed_operations++;
                }
            }
            current_position--;
        }

        if (wasted_moves > c) {
            failed_operations++;
        }
        cout << (failed_operations != 0 ? "NO" : "YES") << endl;
    }
    return 0;
}
