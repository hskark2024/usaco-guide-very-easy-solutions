#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int cube_count;
    cin >> cube_count;

    // We only need each tower's exposed top cube.  Keeping the tops sorted
    // lets us find the best legal tower in logarithmic time.
    vector<int> tower_tops;
    tower_tops.reserve(cube_count);

    for (int index = 0; index < cube_count; ++index) {
        int cube;
        cin >> cube;

        // The new cube must be STRICTLY smaller than the cube below it, so it
        // can go on a tower whose top is > cube.  The smallest such top is the
        // most flexible greedy choice: replacing a larger one would only make
        // the remaining tower tops harder to use later.
        auto tower = upper_bound(tower_tops.begin(), tower_tops.end(), cube);

        if (tower == tower_tops.end()) {
            // No exposed top is large enough.  Every valid construction is
            // therefore forced to start another tower for this cube.
            tower_tops.push_back(cube);
        } else {
            // Put the cube on that tower; it becomes the new exposed top.
            // Sorted order is preserved by the definition of upper_bound.
            *tower = cube;
        }
    }

    cout << tower_tops.size() << '\n';
    return 0;
}
