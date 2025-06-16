#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

int maxDropPoints(const vector<int>& xCoords, const vector<int>& yCoords) {
    unordered_map<int, int> xCount, yCount;
    
   
    for (int x : xCoords) xCount[x]++;
    for (int y : yCoords) yCount[y]++;
    
   
    int maxX = 0, maxY = 0;
    for (const auto& pair : xCount) maxX = max(maxX, pair.second);
    for (const auto& pair : yCount) maxY = max(maxY, pair.second);
  
    return max(maxX, maxY);
}

int main() {
    int xCoordinateSize, yCoordinateSize;
    
    // Read x coordinates
    cin >> xCoordinateSize;
    vector<int> xCoords(xCoordinateSize);
    for (int i = 0; i < xCoordinateSize; i++) {
        cin >> xCoords[i];
    }
    
    // Read y coordinates
    cin >> yCoordinateSize;
    vector<int> yCoords(yCoordinateSize);
    for (int i = 0; i < yCoordinateSize; i++) {
        cin >> yCoords[i];
    }
    
    // Calculate and print the result
    int result = maxDropPoints(xCoords, yCoords);
    cout << result << endl;
    
    return 0;
}