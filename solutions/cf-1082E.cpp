#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int length, target;
    cin >> length >> target;

    vector<int> values(length);
    int largest_value = target;
    for (int &value : values) {
        cin >> value;
        largest_value = max(largest_value, value);
    }

    // Every target value already present is guaranteed to remain useful if we
    // choose an operation outside it (or simply choose k = 0).  We call this
    // the baseline and search only for the largest possible extra gain.
    int target_seen = 0;
    int best_gain = 0;

    // For a fixed non-target value x, choosing k = target - x turns every x in
    // the chosen segment into target.  Inside that same segment, however, each
    // old target stops being target.  Therefore the segment's net gain is:
    //
    //       (# of x values) - (# of target values).
    //
    // ending_gain[x] stores the best such score among segments ending at the
    // most recently processed x.  Other values contribute zero, so we do not
    // need to update x on positions containing unrelated numbers.
    vector<int> ending_gain(largest_value + 1, 0);

    // target_at_last_x[x] lets us lazily count how many target values appeared
    // since x was last processed.  This avoids decreasing the DP value for
    // every possible x whenever we see a target, which would be quadratic.
    vector<int> target_at_last_x(largest_value + 1, 0);

    for (int value : values) {
        if (value == target) {
            ++target_seen;
            continue;
        }

        const int targets_in_gap = target_seen - target_at_last_x[value];

        // Either start a fresh segment at this occurrence (gain 1), or extend
        // the best segment that ended at the previous occurrence of 'value'.
        // Extending adds this new value and loses every target in between.
        ending_gain[value] =
            max(1, ending_gain[value] + 1 - targets_in_gap);

        target_at_last_x[value] = target_seen;
        best_gain = max(best_gain, ending_gain[value]);
    }

    cout << target_seen + best_gain << '\n';
    return 0;
}
