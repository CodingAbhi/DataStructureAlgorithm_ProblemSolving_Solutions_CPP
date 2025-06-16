#include <bits/stdc++.h>

using namespace std;

// Original function from the warmup
vector<size_t> SplitData(size_t data_length, size_t max_packet_size) {
    if (data_length == 0) {
        return {};
    }
    if (max_packet_size == 0) {
        return {}; 
    }
    size_t num_packets = (data_length + max_packet_size - 1) / max_packet_size;
    size_t optimal_size = (data_length + num_packets - 1) / num_packets;
    vector<size_t> result;
    size_t remaining_data = data_length;
    for (size_t i = 0; i < num_packets; ++i) {
        size_t current_packet_size = min(optimal_size, remaining_data);
        result.push_back(current_packet_size);
        remaining_data -= current_packet_size;
    }
    return result;
}

// Function for the follow-up question
vector<size_t> SplitDataWithHeader(size_t data_length, size_t max_packet_size, size_t header_size) {
    if (header_size > max_packet_size) {
        return {}; // Impossible case
    }
    if (data_length == 0) {
        return {header_size}; // Only need to send the header
    }

    size_t total_load = data_length + header_size;
    size_t num_packets = (total_load + max_packet_size - 1) / max_packet_size;
    size_t tentative_optimal_size = (total_load + num_packets - 1) / num_packets;

    if (tentative_optimal_size >= header_size) {
        // Normal Case: The tentative plan is valid.
        return SplitData(total_load, max_packet_size);
    } else {
        // Corner Case: The tentative plan is invalid.
        vector<size_t> result;
        result.push_back(header_size);
        vector<size_t> remaining_packets = SplitData(data_length, max_packet_size);
        result.insert(result.end(), remaining_packets.begin(), remaining_packets.end());
        return result;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    auto test_and_print = [](size_t data_length, size_t max_packet_size, size_t header_size) {
        cout << "Input: data = " << data_length << ", max_pkt = " << max_packet_size << ", header = " << header_size << endl;
        vector<size_t> packets = SplitDataWithHeader(data_length, max_packet_size, header_size);
        cout << "Output: { ";
        for (size_t i = 0; i < packets.size(); ++i) {
            cout << packets[i] << (i == packets.size() - 1 ? "" : ", ");
        }
        cout << " }" << endl << "---" << endl;
    };

    // Normal case
    cout << "--- NORMAL CASES ---" << endl;
    test_and_print(1000, 600, 50);  // total=1050, n=2, opt=525. 525>=50. Should be {525, 525}.
    test_and_print(800, 1000, 100); // total=900, n=1, opt=900. 900>=100. Should be {900}.

    // Corner case from our dry run
    cout << "\n--- CORNER CASES ---" << endl;
    test_and_print(50, 120, 100);  // total=150, n=2, opt=75. 75<100. Should be {100, 50}.
    
    // Another corner case
    test_and_print(10, 120, 100);   // total=110, n=1, opt=110. 110>=100. Normal case: {110}
    test_and_print(10, 105, 100);   // total=110, n=2, opt=55. 55<100. Corner case: {100, 10}

    // Edge cases
    cout << "\n--- EDGE CASES ---" << endl;
    test_and_print(100, 50, 60);    // Impossible case
    test_and_print(0, 100, 50);     // Data is zero

    return 0;
}