#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

// Kattis: Point in Polygon
//
// For every query point, first test whether it lies exactly on a polygon edge.
// Otherwise cast a horizontal ray to the right.  The point is inside exactly
// when that ray crosses an odd number of polygon edges.  A half-open y-range
// rule counts a shared polygon vertex once instead of twice.
struct Point {
    long long x;
    long long y;
};

static __int128 cross(const Point &a, const Point &b, const Point &p) {
    // Exact orientation avoids rounding mistakes for boundary queries.
    return (static_cast<__int128>(b.x) - a.x) *
               (static_cast<__int128>(p.y) - a.y) -
           (static_cast<__int128>(b.y) - a.y) *
               (static_cast<__int128>(p.x) - a.x);
}

static bool on_segment(const Point &a, const Point &b, const Point &p) {
    return cross(a, b, p) == 0 &&
           min(a.x, b.x) <= p.x && p.x <= max(a.x, b.x) &&
           min(a.y, b.y) <= p.y && p.y <= max(a.y, b.y);
}

static const char *classify(const vector<Point> &polygon, const Point &query) {
    bool inside = false;
    const int vertex_count = static_cast<int>(polygon.size());

    for (int i = 0; i < vertex_count; ++i) {
        const Point &a = polygon[i];
        const Point &b = polygon[(i + 1) % vertex_count];

        // Boundary has priority over parity, because the required output has
        // a separate "on" category.
        if (on_segment(a, b, query)) return "on";

        // Exactly one endpoint must be strictly above the query.  Therefore
        // horizontal edges are ignored and a vertex at query.y belongs to
        // only one of its incident edges.
        if ((a.y > query.y) == (b.y > query.y)) continue;

        // Avoid division when asking whether the crossing is to the right.
        // On an upward edge, query is left of the edge when cross > 0.  The
        // sign reverses on a downward edge.
        const __int128 side = cross(a, b, query);
        const bool crosses_right =
            (b.y > a.y && side > 0) || (b.y < a.y && side < 0);
        if (crosses_right) inside = !inside;
    }

    return inside ? "in" : "out";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int vertex_count;
    while (cin >> vertex_count && vertex_count != 0) {
        vector<Point> polygon(vertex_count);
        for (Point &point : polygon) cin >> point.x >> point.y;

        int query_count;
        cin >> query_count;
        while (query_count--) {
            Point query;
            cin >> query.x >> query.y;
            cout << classify(polygon, query) << '\n';
        }
    }
    return 0;
}
