#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>
using namespace std;

// Codeforces 576C: Points on Plane
//
// We do not need the shortest Hamiltonian path.  We only need to stay below
// the generous 2.5e9 Manhattan-distance limit.  Grouping nearby x-coordinates
// and sweeping y in alternating directions gives a simple provable bound.
struct Point {
    int x;
    int y;
    int original_index;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<Point> points(n);
    for (int i = 0; i < n; ++i) {
        cin >> points[i].x >> points[i].y;
        points[i].original_index = i + 1;
    }

    // Coordinates are in [0, 1e6].  Width 1000 creates at most 1001 buckets.
    // Inside one bucket, every horizontal move costs less than 1000.
    constexpr int BUCKET_WIDTH = 1000;

    sort(points.begin(), points.end(), [](const Point &left, const Point &right) {
        const int left_bucket = left.x / BUCKET_WIDTH;
        const int right_bucket = right.x / BUCKET_WIDTH;
        if (left_bucket != right_bucket) return left_bucket < right_bucket;

        // A snake order avoids paying a full vertical reset between buckets:
        // even buckets climb, while odd buckets descend.
        if (left.y != right.y) {
            if (left_bucket % 2 == 0) return left.y < right.y;
            return left.y > right.y;
        }

        // This tie-break is not needed for correctness, but makes the output
        // deterministic when several points have the same y-coordinate.
        if (left.x != right.x) return left.x < right.x;
        return left.original_index < right.original_index;
    });

    for (int i = 0; i < n; ++i) {
        if (i) cout << ' ';
        cout << points[i].original_index;
    }
    cout << '\n';
    return 0;
}
