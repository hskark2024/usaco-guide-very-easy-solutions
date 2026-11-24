#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <set>
#include <vector>
using namespace std;

// Kattis: Segment Intersection
//
// The intersection of two closed segments is either empty, one point, or a
// collinear segment.  Integer cross products classify the exact case without
// floating-point comparisons.  We use long double only after proving that the
// supporting lines have one unique intersection point.
struct Point {
    long long x;
    long long y;

    bool operator<(const Point &other) const {
        return x != other.x ? x < other.x : y < other.y;
    }
};

static __int128 cross(const Point &a, const Point &b, const Point &c) {
    // Cross of vectors a->b and a->c.  __int128 safely handles large integer
    // coordinates and preserves exact collinearity.
    return (static_cast<__int128>(b.x) - a.x) *
               (static_cast<__int128>(c.y) - a.y) -
           (static_cast<__int128>(b.y) - a.y) *
               (static_cast<__int128>(c.x) - a.x);
}

static int sign_of(__int128 value) { return (value > 0) - (value < 0); }

static bool on_segment(const Point &a, const Point &b, const Point &point) {
    return cross(a, b, point) == 0 &&
           min(a.x, b.x) <= point.x && point.x <= max(a.x, b.x) &&
           min(a.y, b.y) <= point.y && point.y <= max(a.y, b.y);
}

static void print_coordinate(long double value) {
    // Avoid printing the visually confusing value -0.00.
    if (fabsl(value) < 0.0005L) value = 0.0L;
    cout << static_cast<double>(value);
}

static void solve_case(const Point &a, const Point &b, const Point &c,
                       const Point &d) {
    const __int128 ab_c = cross(a, b, c);
    const __int128 ab_d = cross(a, b, d);
    const __int128 cd_a = cross(c, d, a);
    const __int128 cd_b = cross(c, d, b);

    // Parallel supporting lines need exact endpoint containment checks.  A set
    // removes duplicates when segments touch at one endpoint or are points.
    if (ab_c == 0 && ab_d == 0 && cd_a == 0 && cd_b == 0) {
        set<Point> common;
        if (on_segment(c, d, a)) common.insert(a);
        if (on_segment(c, d, b)) common.insert(b);
        if (on_segment(a, b, c)) common.insert(c);
        if (on_segment(a, b, d)) common.insert(d);

        if (common.empty()) {
            cout << "none\n";
            return;
        }
        const Point first = *common.begin();
        const Point last = *common.rbegin();
        cout << first.x << ' ' << first.y;
        if (first.x != last.x || first.y != last.y) {
            cout << ' ' << last.x << ' ' << last.y;
        }
        cout << '\n';
        return;
    }

    // Each segment must straddle the other segment's supporting line.  Zero
    // includes legal endpoint touching.
    if (sign_of(ab_c) * sign_of(ab_d) > 0 ||
        sign_of(cd_a) * sign_of(cd_b) > 0) {
        cout << "none\n";
        return;
    }

    const long double rx = static_cast<long double>(b.x) - a.x;
    const long double ry = static_cast<long double>(b.y) - a.y;
    const long double sx = static_cast<long double>(d.x) - c.x;
    const long double sy = static_cast<long double>(d.y) - c.y;
    const long double denominator = rx * sy - ry * sx;

    // Non-collinear parallel lines cannot meet.  This also covers a degenerate
    // point segment that was not caught by the collinear-overlap branch.
    if (denominator == 0.0L) {
        cout << "none\n";
        return;
    }

    const long double cax = static_cast<long double>(c.x) - a.x;
    const long double cay = static_cast<long double>(c.y) - a.y;
    const long double parameter = (cax * sy - cay * sx) / denominator;
    print_coordinate(static_cast<long double>(a.x) + parameter * rx);
    cout << ' ';
    print_coordinate(static_cast<long double>(a.y) + parameter * ry);
    cout << '\n';
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
        solve_case(a, b, c, d);
    }
    return 0;
}
