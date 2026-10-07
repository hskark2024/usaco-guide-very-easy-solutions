#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int pillar_count;
    long long add_cost, remove_cost, move_cost;
    cin >> pillar_count >> add_cost >> remove_cost >> move_cost;

    vector<long long> height(pillar_count);
    long long largest_height = 0;
    for (long long &value : height) {
        cin >> value;
        largest_height = max(largest_height, value);
    }

    // Moving one brick should never cost more than removing that brick and
    // adding a replacement elsewhere.  Capping the price makes the later
    // greedy pairing valid even when the input move operation is expensive.
    move_cost = min(move_cost, add_cost + remove_cost);

    auto total_cost = [&](long long target_height) {
        long long bricks_needed = 0;
        long long bricks_extra = 0;

        for (long long current_height : height) {
            if (current_height < target_height) {
                bricks_needed += target_height - current_height;
            } else {
                bricks_extra += current_height - target_height;
            }
        }

        // Pair an extra brick with a missing brick whenever possible.  Every
        // pair is one move.  Any unmatched deficit needs an add operation,
        // and any unmatched surplus needs a remove operation.
        long long moved = min(bricks_needed, bricks_extra);
        return moved * move_cost
               + (bricks_needed - moved) * add_cost
               + (bricks_extra - moved) * remove_cost;
    };

    // total_cost is convex over integer target heights.  Compare neighboring
    // values to locate the first point where the slope stops being negative.
    long long low = 0;
    long long high = largest_height;
    while (low < high) {
        long long middle = low + (high - low) / 2;
        if (total_cost(middle) <= total_cost(middle + 1)) {
            high = middle;
        } else {
            low = middle + 1;
        }
    }

    cout << total_cost(low) << '\n';
    return 0;
}
