#include <bits/stdc++.h>
using namespace std;
typedef long long nodeLong;

int main() {
    int nodeNumLines;
    cin >> nodeNumLines;
    vector<vector<pair<int, int>>> nodePaths(nodeNumLines);
    map<pair<int, int>, vector<int>> nodePointToSegmentsMap;

    for (int nodeLineIndex = 0; nodeLineIndex < nodeNumLines; nodeLineIndex++) {
        int nodeX1, nodeY1, nodeX2, nodeY2;
        cin >> nodeX1 >> nodeY1 >> nodeX2 >> nodeY2;

        int nodeDeltaX = nodeX2 - nodeX1, nodeDeltaY = nodeY2 - nodeY1;
        int nodeStepCount = max(abs(nodeDeltaX), abs(nodeDeltaY));
        int nodeStepX = (nodeDeltaX == 0) ? 0 : nodeDeltaX / abs(nodeDeltaX);
        int nodeStepY = (nodeDeltaY == 0) ? 0 : nodeDeltaY / abs(nodeDeltaY);

        for (int nodeStep = 0; nodeStep <= nodeStepCount; nodeStep++) {
            int nodeCurrentX = nodeX1 + nodeStepX * nodeStep;
            int nodeCurrentY = nodeY1 + nodeStepY * nodeStep;
            nodePaths[nodeLineIndex].emplace_back(make_pair(nodeCurrentX, nodeCurrentY));
            nodePointToSegmentsMap[{nodeCurrentX, nodeCurrentY}].emplace_back(nodeLineIndex);
        }
    }

    string nodeInput;
    getline(cin, nodeInput);
    getline(cin, nodeInput);
    unordered_map<string, int> nodeValueMap;

    int nodePos = 0, nodeInputLength = nodeInput.size();
    while (nodePos < nodeInputLength) {
        size_t nodeColonPos = nodeInput.find(':', nodePos);
        if (nodeColonPos == string::npos) break;
        string nodeKey = nodeInput.substr(nodePos, nodeColonPos - nodePos);
        nodePos = nodeColonPos + 1;
        size_t nodeSpacePos = nodeInput.find(' ', nodePos);
        if (nodeSpacePos == string::npos) nodeSpacePos = nodeInputLength;
        int nodeValue = stoi(nodeInput.substr(nodePos, nodeSpacePos - nodePos));
        nodeValueMap[nodeKey] = nodeValue;
        nodePos = nodeSpacePos + 1;
    }

    string nodeTarget;
    cin >> nodeTarget;

    nodeLong nodeTotalCost = 0;

    for (auto &nodeEntry : nodePointToSegmentsMap) {
        if (nodeEntry.second.size() >= 2) {
            int nodeOverlapCount = nodeEntry.second.size();
            int nodeMinimumCost = INT_MAX;

            for (auto nodeSegmentID : nodeEntry.second) {
                auto &nodeSegmentPath = nodePaths[nodeSegmentID];
                size_t nodePathLength = nodeSegmentPath.size();
                size_t nodeIndex = find(nodeSegmentPath.begin(), nodeSegmentPath.end(), nodeEntry.first) - nodeSegmentPath.begin();
                int nodeLeftMoves = nodeIndex;
                int nodeRightMoves = nodePathLength - nodeIndex - 1;
                int nodeMoveCost = (nodeLeftMoves > 0 && nodeRightMoves > 0) ? min(nodeLeftMoves, nodeRightMoves) : max(nodeLeftMoves, nodeRightMoves);
                nodeMinimumCost = min(nodeMinimumCost, nodeMoveCost);
            }
            nodeTotalCost += (nodeLong)nodeOverlapCount * nodeMinimumCost;
        }
    }

    if (nodeValueMap.find(nodeTarget) != nodeValueMap.end()) {
        if (nodeTotalCost >= nodeValueMap[nodeTarget]) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    } else {
        cout << "No\n";
    }

    int nodeValidKeyCount = 0, nodeTotalKeyCount = nodeValueMap.size();
    for (auto &nodeEntry : nodeValueMap) {
        if (nodeTotalCost >= nodeEntry.second) {
            nodeValidKeyCount++;
        }
    }

    double nodeSuccessRate = (double)nodeValidKeyCount / nodeTotalKeyCount;
    cout << fixed << setprecision(2) << nodeSuccessRate;

    return 0;
}
