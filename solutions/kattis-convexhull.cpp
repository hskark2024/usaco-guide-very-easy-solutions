#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

// Kattis: Convex Hull
//
// Andrew's monotone-chain algorithm builds the lower and upper boundaries of
// the smallest convex polygon containing every input point.  Sorting is the
// only O(N log N) step; each point is pushed and popped at most once per chain.
struct Point {
    long long x;
    long long y;

    bool operator<(const Point &other) const {
        return x != other.x ? x < other.x : y < other.y;
    }

    bool operator==(const Point &other) const {
        return x == other.x && y == other.y;
    }
};

static long long cross(const Point &origin, const Point &first,
                       const Point &second) {
    // Positive means origin -> first -> second turns left.  The coordinate
    // bound is 10^4, so signed 64-bit arithmetic is comfortably sufficient.
    return (first.x - origin.x) * (second.y - origin.y) -
           (first.y - origin.y) * (second.x - origin.x);
}

static vector<Point> convex_hull(vector<Point> points) {
    sort(points.begin(), points.end());

    // Repeated coordinates describe the same geometric point.  Removing them
    // also makes the one-point and all-identical cases straightforward.
    points.erase(unique(points.begin(), points.end()), points.end());
    if (points.size() <= 1) return points;

    vector<Point> hull;
    hull.reserve(points.size() * 2);

    // Visit left to right.  Whenever the newest three points fail to make a
    // strict left turn, the middle point cannot be a corner of the lower hull.
    // Popping on cross == 0 deliberately removes collinear edge points, as the
    // statement requests a polygon without collinear consecutive edges.
    for (const Point &point : points) {
        while (hull.size() >= 2 &&
               cross(hull[hull.size() - 2], hull.back(), point) <= 0) {
            hull.pop_back();
        }
        hull.push_back(point);
    }

    // The lower chain already ends at the rightmost point.  Remember its size
    // so upper-chain popping never removes a point belonging only to the lower
    // construction.
    const size_t lower_size = hull.size();

    // Walk back from right to left to create the upper boundary.  Starting at
    // size-2 avoids inserting the rightmost endpoint twice.
    for (int index = static_cast<int>(points.size()) - 2; index >= 0; --index) {
        const Point &point = points[index];
        while (hull.size() > lower_size &&
               cross(hull[hull.size() - 2], hull.back(), point) <= 0) {
            hull.pop_back();
        }
        hull.push_back(point);
    }

    // The final point repeats the leftmost starting point to close the walk.
    // Kattis wants each polygon vertex printed exactly once.
    hull.pop_back();
    return hull;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int point_count;
    while (cin >> point_count && point_count != 0) {
        vector<Point> points(point_count);
        for (Point &point : points) cin >> point.x >> point.y;

        const vector<Point> hull = convex_hull(points);
        cout << hull.size() << '\n';
        for (const Point &point : hull) {
            cout << point.x << ' ' << point.y << '\n';
        }
    }
    return 0;
}
