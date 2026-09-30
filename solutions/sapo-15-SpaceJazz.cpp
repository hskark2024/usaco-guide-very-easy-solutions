#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string performance;
    cin >> performance;

    const int note_count = static_cast<int>(performance.size());

    // additions[left][right] is the fewest missing notes needed to turn the
    // inclusive substring performance[left..right] into valid space jazz.
    // We allocate one extra row and column so an empty interval naturally has
    // cost zero; this makes the split recurrence work at both boundaries.
    vector<vector<int>> additions(
        note_count + 1,
        vector<int>(note_count + 1, 0)
    );

    // Every transition uses strictly shorter intervals, so process lengths
    // from one note upward.
    for (int length = 1; length <= note_count; ++length) {
        for (int left = 0; left + length <= note_count; ++left) {
            const int right = left + length - 1;

            // Safe fallback: insert a copy of the first note next to it.  That
            // pair can be removed together, leaving the rest of the interval.
            additions[left][right] = 1 + additions[left + 1][right];

            // Instead of inserting a copy, the first observed note may pair
            // with an equal observed note at `partner`.  Noncrossing pairs
            // force the notes between and after them to form independent
            // valid pieces, whose optimal costs can simply be added.
            for (int partner = left + 1; partner <= right; ++partner) {
                if (performance[left] != performance[partner]) {
                    continue;
                }

                const int inside_cost = additions[left + 1][partner - 1];
                const int suffix_cost = additions[partner + 1][right];
                additions[left][right] = min(
                    additions[left][right],
                    inside_cost + suffix_cost
                );
            }
        }
    }

    cout << additions[0][note_count - 1] << '\n';
    return 0;
}
