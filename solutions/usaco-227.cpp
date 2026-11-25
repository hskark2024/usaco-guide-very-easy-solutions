#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <set>
#include <utility>
#include <vector>
using namespace std;

// USACO 2013 January Silver: Square Overlap
//
// All squares are axis-aligned and have the same side length K.  Two of them
// share positive area exactly when both center gaps are strictly smaller than
// K.  We sort centers by x and maintain only earlier centers whose x gap is
// still smaller than K.  A set ordered by y then finds possible overlaps in a
// narrow vertical band.

struct Center {
    long long x;
    long long y;
    int id;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int square_count;
    long long side_length;
    cin >> square_count >> side_length;

    vector<Center> centers(square_count);
    for (int index = 0; index < square_count; ++index) {
        cin >> centers[index].x >> centers[index].y;
        centers[index].id = index;
    }

    sort(centers.begin(), centers.end(), [](const Center &first,
                                            const Center &second) {
        if (first.x != second.x) return first.x < second.x;
        if (first.y != second.y) return first.y < second.y;
        return first.id < second.id;
    });

    // Each active entry is (y, sorted index).  The sorted index makes entries
    // unique even when several centers have the same y-coordinate.
    set<pair<long long, int>> active_by_y;
    int left = 0;
    int overlap_count = 0;
    long long unique_overlap_area = 0;

    for (int right = 0; right < square_count; ++right) {
        const Center &current = centers[right];

        // A horizontal gap of K means the borders only touch, so it is not a
        // positive-area overlap.  Remove those and every older center.
        while (left < right && current.x - centers[left].x >= side_length) {
            active_by_y.erase({centers[left].y, left});
            ++left;
        }

        // Coordinates are integral.  Strict |dy| < K is equivalent to
        // y-K+1 <= other_y <= y+K-1, which this half-open set range expresses.
        auto candidate = active_by_y.lower_bound(
            {current.y - side_length + 1, -1});
        const auto finish = active_by_y.lower_bound(
            {current.y + side_length, -1});

        for (; candidate != finish; ++candidate) {
            const Center &other = centers[candidate->second];
            ++overlap_count;

            // The task asks for -1 as soon as more than one pair overlaps.
            // Stopping here also prevents a dense input from making the range
            // scan quadratic.
            if (overlap_count > 1) {
                cout << -1 << '\n';
                return 0;
            }

            const long long overlap_width =
                side_length - llabs(current.x - other.x);
            const long long overlap_height =
                side_length - llabs(current.y - other.y);
            unique_overlap_area = overlap_width * overlap_height;
        }

        active_by_y.insert({current.y, right});
    }

    // No pair leaves the initialized area at zero; exactly one pair stores
    // its positive intersection area above.
    cout << unique_overlap_area << '\n';
    return 0;
}
