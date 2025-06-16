#include <bits/stdc++.h>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int salaryRounding(int salary) {
    return ceil(salary / 2.0);
}

int salaryReduction(int salary, int B) {
    return max(0, salary - B);
}

int main() {
    int N, B, K1, K2;
    cin >> N >> B >> K1 >> K2;

    vector<int> salaries(N);
    for (int i = 0; i < N; ++i) {
        cin >> salaries[i];
    }

    sort(salaries.begin(), salaries.end(), greater<int>());

    for (int i = 0; i < N && K1 > 0; ++i) {
        salaries[i] = salaryRounding(salaries[i]);
        --K1;
    }

    for (int i = 0; i < N && K2 > 0; ++i) {
        salaries[i] = salaryReduction(salaries[i], B);
        --K2;
    }

    int totalReducedSalary = 0;
    for (int i = 0; i < N; ++i) {
        totalReducedSalary += salaries[i];
    }

    cout << totalReducedSalary << endl;

    return 0;
}
