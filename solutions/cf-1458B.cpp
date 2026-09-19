#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> capacity(n), water(n);
    int total_capacity = 0, total_water = 0;
    for (int i = 0; i < n; ++i) {
        cin >> capacity[i] >> water[i];
        total_capacity += capacity[i];
        total_water += water[i];
    }

    // For a chosen set, let C be its capacity and B its initial water.
    // Keep B without loss, then pour directly from unchosen glasses: only
    // half of their total_water - B arrives. The best possible retained
    // amount is min(C, B + (total_water - B) / 2).
    // Thus, for fixed count and capacity, a larger B is always at least as
    // good. We can discard every other subset with those same two keys.
    const int IMPOSSIBLE = -1;  // Zero water is valid, so it cannot be a sentinel.
    vector<vector<int>> best(n + 1, vector<int>(total_capacity + 1, IMPOSSIBLE));
    best[0][0] = 0;  // The empty selection has zero capacity and zero water.

    int processed_capacity = 0;
    for (int i = 0; i < n; ++i) {
        // Descending count ensures row count-1 still excludes this glass.
        // Descending capacity also follows the usual 0/1 knapsack order.
        // Never use a glass twice: each one is a distinct physical object.
        for (int count = i + 1; count >= 1; --count) {
            for (int old_capacity = processed_capacity; old_capacity >= 0; --old_capacity) {
                if (best[count - 1][old_capacity] == IMPOSSIBLE) {
                    continue;  // An unreachable subset cannot grow into a real one.
                }
                const int new_capacity = old_capacity + capacity[i];
                best[count][new_capacity] = max(
                    best[count][new_capacity],
                    best[count - 1][old_capacity] + water[i]
                );
                // Leaving best[count][new_capacity] unchanged represents
                // skipping this glass; taking it adds its full initial water.
            }
        }
        processed_capacity += capacity[i];
    }

    cout << fixed << setprecision(10);
    for (int count = 1; count <= n; ++count) {
        int answer_twice = 0;
        for (int c = 0; c <= total_capacity; ++c) {
            if (best[count][c] == IMPOSSIBLE) continue;
            // Doubling avoids rounding during comparisons. Every optimum
            // is an integer or a half-integer; only output needs floating point.
            answer_twice = max(answer_twice, min(2 * c, total_water + best[count][c]));
        }
        if (count > 1) cout << ' ';
        cout << answer_twice / 2.0;
    }
    cout << '\n';
    return 0;
}
