#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int criminal_count, car_capacity;
    cin >> criminal_count >> car_capacity;

    vector<long long> position(criminal_count);
    for (long long &coordinate : position) {
        cin >> coordinate;
    }

    // left_cost[i] is the one-way distance needed to collect everyone left
    // of a station at position[i].  With capacity m, start with the farthest
    // criminal and collect the next m-1 criminals while returning.  Thus the
    // farthest members of the left-side trips have indices 0, m, 2m, ... .
    vector<long long> left_cost(criminal_count, 0);
    long long selected_position_sum = 0;
    long long trip_count = 0;

    for (int station = 1; station < criminal_count; ++station) {
        int newly_left = station - 1;

        // This criminal becomes the farthest member of a new trip exactly
        // when its index is a multiple of the car capacity.
        if (newly_left % car_capacity == 0) {
            selected_position_sum += position[newly_left];
            ++trip_count;
        }

        // Sum(position[station] - selected_position) over all left trips.
        left_cost[station] =
            trip_count * position[station] - selected_position_sum;
    }

    // Mirror the same calculation from right to left.  The farthest members
    // of right-side trips have indices n-1, n-1-m, n-1-2m, ... .
    vector<long long> right_cost(criminal_count, 0);
    selected_position_sum = 0;
    trip_count = 0;

    for (int station = criminal_count - 2; station >= 0; --station) {
        int newly_right = station + 1;
        if ((criminal_count - 1 - newly_right) % car_capacity == 0) {
            selected_position_sum += position[newly_right];
            ++trip_count;
        }

        // Sum(selected_position - position[station]) over all right trips.
        right_cost[station] =
            selected_position_sum - trip_count * position[station];
    }

    long long best_one_way_distance = numeric_limits<long long>::max();
    for (int station = 0; station < criminal_count; ++station) {
        // A best station can be chosen at a criminal's coordinate: between
        // neighboring coordinates, the trip groups stay fixed and the cost
        // is linear, so an interval minimum occurs at an endpoint.
        best_one_way_distance = min(
            best_one_way_distance,
            left_cost[station] + right_cost[station]
        );
    }

    // Every collecting trip travels out from the station and returns.
    cout << 2LL * best_one_way_distance << '\n';
    return 0;
}
