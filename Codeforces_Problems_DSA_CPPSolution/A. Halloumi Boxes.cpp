#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Interval {
    int start, end;
};

int hardycount(vector<int>& start, vector<int>& end) {
    int n = start.size();
    vector<Interval> intval(n);

    for (int i = 0; i < n; i++) {
        intval[i].start = start[i];
        intval[i].end = end[i];
    }

    sort(intval.begin(), intval.end(), [](const Interval& a, const Interval& b) {
        return a.start < b.start || (a.start == b.start && a.end < b.end);
    });

    int count = 0;
    
 
    for (int i = 0; i < n; i++) {
        int j = i + 1;
        while (j < n && intval[j].start <= intval[i].end) j++;

        while (j < n - 1) { 
            int k = j + 1;
            while (k < n && intval[k].start <= intval[j].end) k++;

    
            while (k < n) {
                count++;
                k++;
            }

            j++;
        }
    }

    return count;
}

int main() {
    vector<int> start = {1, 2, 4, 3, 7};
    vector<int> end = {3, 4, 6, 5, 8};
    
    cout << "Number of non-overlapping interval trios: " << hardycount(start, end) << endl;
    return 0;
}
