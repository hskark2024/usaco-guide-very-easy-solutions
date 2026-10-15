#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int member_count;
    cin >> member_count;

    vector<long long> speed(member_count);
    for (long long &value : speed) cin >> value;
    sort(speed.begin(), speed.end());

    // interval_cost[left][right] is the smallest total discrepancy for an
    // ordering that uses exactly the sorted interval [left, right].
    // A one-person prefix has discrepancy zero, so the diagonal starts at 0.
    vector<vector<long long>> interval_cost(
        member_count, vector<long long>(member_count, 0));

    // Work from short intervals to long intervals. In an optimal order for
    // [left, right], the last-added runner can be chosen as one of the two
    // extremes. Removing that last extreme leaves a smaller contiguous
    // interval, and the full interval contributes speed[right]-speed[left].
    for (int length = 2; length <= member_count; ++length) {
        for (int left = 0; left + length <= member_count; ++left) {
            const int right = left + length - 1;

            const long long without_smallest = interval_cost[left + 1][right];
            const long long without_largest = interval_cost[left][right - 1];
            const long long current_discrepancy = speed[right] - speed[left];

            interval_cost[left][right] =
                min(without_smallest, without_largest) + current_discrepancy;
        }
    }

    cout << interval_cost[0][member_count - 1] << '\n';
    return 0;
}
