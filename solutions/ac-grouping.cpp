#include <algorithm>
#include <cstdint>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int rabbit_count;
    cin >> rabbit_count;

    vector<vector<int64_t>> affinity(
        rabbit_count,
        vector<int64_t>(rabbit_count)
    );
    for (int first = 0; first < rabbit_count; ++first) {
        for (int second = 0; second < rabbit_count; ++second) {
            cin >> affinity[first][second];
        }
    }

    const uint32_t state_count = uint32_t{1} << rabbit_count;

    // group_score[mask] is the score earned if every rabbit in mask belongs
    // to one group.  Values and totals can exceed 32-bit signed integers.
    vector<int64_t> group_score(state_count, 0);
    for (uint32_t mask = 1; mask < state_count; ++mask) {
        // Remove one rabbit.  Its new contribution is exactly its affinity
        // with every rabbit already in the smaller group.
        const uint32_t rabbit_bit = mask & -mask;
        const int rabbit = __builtin_ctz(rabbit_bit);
        const uint32_t remainder = mask ^ rabbit_bit;

        group_score[mask] = group_score[remainder];
        uint32_t partners = remainder;
        while (partners != 0) {
            const int partner = __builtin_ctz(partners);
            partners &= partners - 1;
            group_score[mask] += affinity[rabbit][partner];
        }
    }

    // best[mask] is the maximum score from partitioning exactly mask into any
    // number of nonempty groups.  The empty set has score zero.
    vector<int64_t> best(
        state_count,
        numeric_limits<int64_t>::lowest()
    );
    best[0] = 0;

    for (uint32_t mask = 1; mask < state_count; ++mask) {
        // In every partition, exactly one group contains this anchor rabbit.
        // Requiring the chosen submask to contain it removes duplicate group
        // orderings without removing any possible partition.
        const uint32_t anchor_bit = mask & -mask;

        for (uint32_t group = mask; group != 0;
             group = (group - 1) & mask) {
            if ((group & anchor_bit) == 0) {
                continue;
            }

            const uint32_t remainder = mask ^ group;
            best[mask] = max(
                best[mask],
                group_score[group] + best[remainder]
            );
        }
    }

    cout << best[state_count - 1] << '\n';
    return 0;
}
