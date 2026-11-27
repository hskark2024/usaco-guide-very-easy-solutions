#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

// Kattis: Robert Hood
//
// A farthest pair must lie on the convex hull.  We first discard all interior
// points with monotone chain, then use rotating calipers to inspect every
// antipodal hull pair in linear time.
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
    return (first.x - origin.x) * (second.y - origin.y) -
           (first.y - origin.y) * (second.x - origin.x);
}

static long long distance_squared(const Point &first, const Point &second) {
    const long long dx = first.x - second.x;
    const long long dy = first.y - second.y;
    return dx * dx + dy * dy;
}

static vector<Point> convex_hull(vector<Point> points) {
    sort(points.begin(), points.end());
    points.erase(unique(points.begin(), points.end()), points.end());
    if (points.size() <= 1) return points;

    vector<Point> hull;

    // Build the lower hull, keeping only strict counterclockwise corners.
    for (const Point &point : points) {
        while (hull.size() >= 2 &&
               cross(hull[hull.size() - 2], hull.back(), point) <= 0) {
            hull.pop_back();
        }
        hull.push_back(point);
    }

    const size_t lower_size = hull.size();

    // Build the upper hull in reverse sorted order.
    for (int index = static_cast<int>(points.size()) - 2; index >= 0; --index) {
        const Point &point = points[index];
        while (hull.size() > lower_size &&
               cross(hull[hull.size() - 2], hull.back(), point) <= 0) {
            hull.pop_back();
        }
        hull.push_back(point);
    }

    hull.pop_back();  // Remove the duplicated first point.
    return hull;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int shot_count;
    cin >> shot_count;
    vector<Point> shots(shot_count);
    for (Point &shot : shots) cin >> shot.x >> shot.y;

    const vector<Point> hull = convex_hull(shots);
    const int hull_size = static_cast<int>(hull.size());

    // Duplicate arrows can reduce the hull to one point, although ordinary
    // contest data normally contains at least two distinct hit positions.
    long long best_squared = 0;
    if (hull_size == 2) {
        best_squared = distance_squared(hull[0], hull[1]);
    } else if (hull_size >= 3) {
        int opposite = 1;

        for (int edge_start = 0; edge_start < hull_size; ++edge_start) {
            const int edge_end = (edge_start + 1) % hull_size;

            // For a fixed hull edge, advance the opposite point while the
            // triangle area grows.  Convexity makes these areas unimodal, so
            // the pointer completes at most one trip around the hull overall.
            while (true) {
                const int next_opposite = (opposite + 1) % hull_size;
                const long long current_area =
                    abs(cross(hull[edge_start], hull[edge_end], hull[opposite]));
                const long long next_area =
                    abs(cross(hull[edge_start], hull[edge_end],
                              hull[next_opposite]));
                if (next_area <= current_area) break;
                opposite = next_opposite;
            }

            // Both endpoints of the current supporting edge can form the
            // diameter with the current antipodal point.
            best_squared = max(best_squared,
                               distance_squared(hull[edge_start], hull[opposite]));
            best_squared = max(best_squared,
                               distance_squared(hull[edge_end], hull[opposite]));
        }
    }

    cout << fixed << setprecision(10)
         << sqrt(static_cast<long double>(best_squared)) << '\n';
    return 0;
}
