#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

using int64 = long long;

// Build prefix_score[p]: the greatest total base length obtainable from p
// disjoint pairs on one horizontal line.
//
// After sorting, an exchange argument says the best first pair uses the
// leftmost and rightmost points.  Removing them leaves the same problem on a
// smaller interval, so every next pair also takes the remaining extremes.
static vector<int64> build_pair_scores(vector<int64> coordinates) {
    sort(coordinates.begin(), coordinates.end());

    const int point_count = static_cast<int>(coordinates.size());
    const int pair_count = point_count / 2;
    vector<int64> prefix_score(pair_count + 1, 0);

    for (int pairs_used = 1; pairs_used <= pair_count; ++pairs_used) {
        const int left_index = pairs_used - 1;
        const int right_index = point_count - pairs_used;

        // The two horizontal lines are distance 2 apart.  A triangle whose
        // horizontal base has length d therefore has area d * 2 / 2 = d.
        const int64 next_area =
            coordinates[right_index] - coordinates[left_index];
        prefix_score[pairs_used] =
            prefix_score[pairs_used - 1] + next_area;
    }

    return prefix_score;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int test_count;
    cin >> test_count;

    while (test_count--) {
        int lower_count, upper_count;
        cin >> lower_count >> upper_count;

        vector<int64> lower_x(lower_count);
        vector<int64> upper_x(upper_count);
        for (int64 &coordinate : lower_x) {
            cin >> coordinate;
        }
        for (int64 &coordinate : upper_x) {
            cin >> coordinate;
        }

        const vector<int64> lower_score = build_pair_scores(lower_x);
        const vector<int64> upper_score = build_pair_scores(upper_x);

        // Every non-collinear triangle consumes at least one point from each
        // line and three points overall.  These three resource limits are
        // also sufficient, so their minimum is exactly k_max.
        const int maximum_triangles = min({
            lower_count,
            upper_count,
            (lower_count + upper_count) / 3,
        });

        cout << maximum_triangles << '\n';
        if (maximum_triangles == 0) {
            continue;
        }

        for (int triangle_count = 1;
             triangle_count <= maximum_triangles;
             ++triangle_count) {
            // Let lower_pairs be the number of triangles whose two same-line
            // points come from y = 0.  The remaining triangles use a pair
            // from y = 2.
            //
            // Points consumed below: 2*lower_pairs + upper_pairs
            //                       = lower_pairs + triangle_count.
            // Points consumed above: lower_pairs + 2*upper_pairs
            //                       = 2*triangle_count - lower_pairs.
            // Rearranging both capacity limits gives this feasible interval.
            int left = max(0, 2 * triangle_count - upper_count);
            int right = min(triangle_count, lower_count - triangle_count);

            auto score = [&](int lower_pairs) -> int64 {
                const int upper_pairs = triangle_count - lower_pairs;
                return lower_score[lower_pairs] + upper_score[upper_pairs];
            };

            // Pair gains on each line decrease as more extreme points are
            // removed.  Consequently score(lower_pairs) is a discrete
            // concave function: it rises to one peak, then falls.  Comparing
            // neighboring values finds that peak with a binary search.
            while (left < right) {
                const int middle = left + (right - left) / 2;
                if (score(middle) <= score(middle + 1)) {
                    left = middle + 1;
                } else {
                    right = middle;
                }
            }

            cout << score(left)
                 << (triangle_count == maximum_triangles ? '\n' : ' ');
        }
    }

    return 0;
}
