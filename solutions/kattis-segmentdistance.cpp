#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
using namespace std;

// Kattis: Segment Distance
//
// The closest pair of points on two closed segments has distance zero when
// the segments intersect.  Otherwise at least one point in the closest pair
// is an endpoint, so it is enough to check all four endpoint-to-segment
// distances.  Integer cross products classify intersection exactly; floating
// point is used only for Euclidean distance and projection.
struct Point {
    long long x;
    long long y;
};

static __int128 cross(const Point &a, const Point &b, const Point &c) {
    // This is the signed area of the parallelogram formed by a->b and a->c.
    // A positive value means c is left of the directed line a->b.
    return (static_cast<__int128>(b.x) - a.x) *
               (static_cast<__int128>(c.y) - a.y) -
           (static_cast<__int128>(b.y) - a.y) *
               (static_cast<__int128>(c.x) - a.x);
}

static int sign_of(__int128 value) {
    return (value > 0) - (value < 0);
}

static bool on_segment(const Point &a, const Point &b, const Point &p) {
    // Collinearity alone is not enough: p must also lie inside both coordinate
    // ranges of the closed segment.
    return cross(a, b, p) == 0 &&
           min(a.x, b.x) <= p.x && p.x <= max(a.x, b.x) &&
           min(a.y, b.y) <= p.y && p.y <= max(a.y, b.y);
}

static bool segments_intersect(const Point &a, const Point &b,
                               const Point &c, const Point &d) {
    const __int128 ab_c = cross(a, b, c);
    const __int128 ab_d = cross(a, b, d);
    const __int128 cd_a = cross(c, d, a);
    const __int128 cd_b = cross(c, d, b);

    // Deal with all boundary contacts first, including collinear overlap and
    // a segment that has collapsed to one point.
    if (ab_c == 0 && on_segment(a, b, c)) return true;
    if (ab_d == 0 && on_segment(a, b, d)) return true;
    if (cd_a == 0 && on_segment(c, d, a)) return true;
    if (cd_b == 0 && on_segment(c, d, b)) return true;

    // A proper crossing has opposite strict orientation signs both ways.
    return sign_of(ab_c) * sign_of(ab_d) < 0 &&
           sign_of(cd_a) * sign_of(cd_b) < 0;
}

static long double point_to_segment_distance(const Point &p, const Point &a,
                                             const Point &b) {
    const long double ab_x = static_cast<long double>(b.x) - a.x;
    const long double ab_y = static_cast<long double>(b.y) - a.y;
    const long double ap_x = static_cast<long double>(p.x) - a.x;
    const long double ap_y = static_cast<long double>(p.y) - a.y;
    const long double length_squared = ab_x * ab_x + ab_y * ab_y;

    // A zero-length segment is just the point a, so projection would divide
    // by zero.  Handle it directly.
    if (length_squared == 0.0L) return hypotl(ap_x, ap_y);

    // Parameter t locates the perpendicular projection on the infinite line.
    // Clamping t to [0, 1] moves that point onto the closed segment.
    long double t = (ap_x * ab_x + ap_y * ab_y) / length_squared;
    t = max(0.0L, min(1.0L, t));
    const long double closest_x = static_cast<long double>(a.x) + t * ab_x;
    const long double closest_y = static_cast<long double>(a.y) + t * ab_y;
    return hypotl(static_cast<long double>(p.x) - closest_x,
                  static_cast<long double>(p.y) - closest_y);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(2);

    int test_count;
    cin >> test_count;
    while (test_count--) {
        Point a, b, c, d;
        cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y >> d.x >> d.y;

        if (segments_intersect(a, b, c, d)) {
            cout << "0.00\n";
            continue;
        }

        // If the segments are disjoint, an endpoint participates in some
        // closest pair.  Try both endpoints from each segment symmetrically.
        const long double answer = min({
            point_to_segment_distance(a, c, d),
            point_to_segment_distance(b, c, d),
            point_to_segment_distance(c, a, b),
            point_to_segment_distance(d, a, b),
        });
        cout << static_cast<double>(answer) << '\n';
    }
    return 0;
}
