#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

// POI 2017: Containers
//
// An operation adds one container at a, a+d, ..., a+(length-1)d.  Directly
// visiting every position can be quadratic.  Split operations by step size:
// large steps touch few positions, while all operations with one small step
// can be combined in a single difference-array sweep.
struct SmallOperation {
    int first;
    int stop;  // one progression step after the final affected position
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int position_count, operation_count;
    cin >> position_count >> operation_count;

    // About sqrt(100000).  The total work is roughly
    // LIMIT*N + K*N/LIMIT, which is safely linear-times-square-root.
    constexpr int LIMIT = 320;

    vector<vector<SmallOperation>> grouped(LIMIT + 1);
    vector<int> answer(position_count + 1, 0);

    for (int operation = 0; operation < operation_count; ++operation) {
        int first, length, step;
        cin >> first >> length >> step;

        if (step <= LIMIT) {
            // Saving only the endpoints lets us combine every operation that
            // has this step before doing one sweep of the whole ramp.
            grouped[step].push_back({first, first + length * step});
        } else {
            // A large step visits at most N/(LIMIT+1) positions, so explicit
            // simulation is cheap enough.
            int position = first;
            for (int placed = 0; placed < length; ++placed) {
                ++answer[position];
                position += step;
            }
        }
    }

    vector<int> difference(position_count + LIMIT + 2, 0);
    for (int step = 1; step <= LIMIT; ++step) {
        if (grouped[step].empty()) continue;

        // The same buffer is reused for each step, keeping memory O(N+K)
        // instead of storing a separate N-cell table for every small step.
        fill(difference.begin(), difference.end(), 0);
        for (const SmallOperation &operation : grouped[step]) {
            ++difference[operation.first];
            --difference[operation.stop];
        }

        for (int position = 1; position <= position_count; ++position) {
            // position-step is the previous cell in the same residue class.
            if (position > step) {
                difference[position] += difference[position - step];
            }
            answer[position] += difference[position];
        }
    }

    for (int position = 1; position <= position_count; ++position) {
        if (position > 1) cout << ' ';
        cout << answer[position];
    }
    cout << '\n';
    return 0;
}
