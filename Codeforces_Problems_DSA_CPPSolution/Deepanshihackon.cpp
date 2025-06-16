#include <bits/stdc++.h>
#include <string>

using namespace std;


int binaryToDecimal(const string& binaryStr) {
    return stoi(binaryStr, nullptr, 2);
}


int sumOfDigits(int n) {
    int sum = 0;
    while (n > 0) {
        sum += n % 10;
        n /= 10;
    }
    return sum;
}


int countAdditionOperations(const string& binaryStr) {
    int decimalNumber = binaryToDecimal(binaryStr);
    int operationsCount = 0;

    while (decimalNumber >= 10) {
        decimalNumber = sumOfDigits(decimalNumber);
        operationsCount++;
    }

    return operationsCount;
}

int main() {
    // Sample Input
    string binaryInput ;
    cin>>binaryInput;
    cout << countAdditionOperations(binaryInput) << endl; // Output: 0
    return 0;
}
