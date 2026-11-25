#include <algorithm>
#include <iostream>
#include <map>
#include <numeric>
#include <utility>
#include <vector>
using namespace std;

// LeetCode 149: Max Points on a Line
//
// The judge's original interface is a class method.  This repository uses a
// small stdin/stdout wrapper so the same algorithm can be compiled and tested
// locally: read n, then n pairs (x, y), and print the maximum count.
//
// For one fixed anchor point, every other point belongs to exactly one line
// through that anchor.  We identify that line by a reduced integer direction
// (dx, dy).  Reducing by gcd and choosing one sign convention avoids floating
// point slopes and makes opposite-looking vectors describe the same line.

struct Point {
    long long x;
    long long y;
};

static pair<long long, long long> normalized_direction(const Point &from,
                                                       const Point &to) {
    long long dx = to.x - from.x;
    long long dy = to.y - from.y;

    // Divide out every common factor.  For example, (6, 9) and (2, 3)
    // both become the canonical direction (2, 3).
    const long long divisor = gcd(abs(dx), abs(dy));
    dx /= divisor;
    dy /= divisor;

    // A line has no preferred direction.  Force dx to be positive; for a
    // vertical line, force dy to be positive.  Thus (2, 3) and (-2, -3)
    // receive the same key, as do (0, 1) and (0, -1).
    if (dx < 0 || (dx == 0 && dy < 0)) {
        dx = -dx;
        dy = -dy;
    }
    return {dx, dy};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int point_count;
    cin >> point_count;
    vector<Point> points(point_count);
    for (Point &point : points) cin >> point.x >> point.y;

    // A single point is itself the largest collinear set.
    int answer = min(point_count, 1);

    for (int anchor = 0; anchor < point_count; ++anchor) {
        map<pair<long long, long long>, int> frequency;
        int best_through_anchor = 0;

        // Count only later points.  Any optimal line has a first point in
        // index order, so that line is fully counted when that point is the
        // anchor.  This saves work without changing the answer.
        for (int other = anchor + 1; other < point_count; ++other) {
            const auto direction =
                normalized_direction(points[anchor], points[other]);
            best_through_anchor = max(best_through_anchor, ++frequency[direction]);
        }

        // The map counts points other than the anchor, so add the anchor.
        answer = max(answer, best_through_anchor + 1);

        // Even if all remaining points joined one line, they could not beat
        // the current answer.  This is only an optimization; correctness does
        // not depend on it.
        if (answer >= point_count - anchor) break;
    }

    cout << answer << '\n';
    return 0;
}
