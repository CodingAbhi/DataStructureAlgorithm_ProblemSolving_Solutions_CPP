#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Event {
    string badge_id;   // unique to each employee
    bool is_entry;     // if false, event is an exit
    int timestamp;     // seconds since midnight
};

void findMaxOccupancy(vector<Event> events) {
    // Step 1: Sort events by timestamp
    sort(events.begin(), events.end(), [](const Event& a, const Event& b) {
        return a.timestamp < b.timestamp;
    });

    int current_occupancy = 0;
    int max_occupancy = 0;
    int time_of_max = 0;

    // Step 2: Process each event
    for (const auto& event : events) {
        if (event.is_entry) {
            current_occupancy++;
        } else {
            current_occupancy--;
        }

        if (current_occupancy > max_occupancy) {
            max_occupancy = current_occupancy;
            time_of_max = event.timestamp;
        }
    }

    cout << "Max occupancy: " << max_occupancy
         << " at time: " << time_of_max << endl;
}

int main() {
    vector<Event> events = {
        {"abc", true, 12},
        {"abd", true, 14},
        {"abc", false, 14},
        {"abe", true, 11},
        {"abd", false, 15},
        {"abe", false, 15},

    };

    findMaxOccupancy(events);

    return 0;
}
