#include <algorithm>
#include <cmath>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

// IOI 2003: Seeing the Boundary
//
// Every convex rock covers one continuous interval of viewing directions.
// We turn the two tangent rays into an inclusive interval of integer fence-post
// positions, merge all such intervals, and subtract their union from 4*N.

struct Point {
    long long x;
    long long y;
};

struct Fraction {
    long long numerator;
    long long denominator;  // Always positive.
};

static long long ceil_fraction(const Fraction &value) {
    // All perimeter coordinates are nonnegative.
    return (value.numerator + value.denominator - 1) / value.denominator;
}

static long long floor_fraction(const Fraction &value) {
    return value.numerator / value.denominator;
}

// Continue the ray origin + t*direction until it first meets the square.
// Return the hit point as a rational coordinate on this counterclockwise
// perimeter numbering:
//   (0,0) -> (N,0) -> (N,N) -> (0,N) -> (0,0).
static Fraction perimeter_hit(long long side, const Point &origin,
                              const Point &direction) {
    long long best_numerator = 0;
    long long best_denominator = 1;
    int hit_side = -1;  // 0 bottom, 1 right, 2 top, 3 left.

    auto consider = [&](long long numerator, long long denominator, int side_id) {
        // Compare numerator/denominator without floating point. Products are
        // at most 500000^2 under the official limits.
        if (hit_side == -1 ||
            numerator * best_denominator < best_numerator * denominator) {
            best_numerator = numerator;
            best_denominator = denominator;
            hit_side = side_id;
        }
    };

    if (direction.x > 0) {
        consider(side - origin.x, direction.x, 1);
    } else if (direction.x < 0) {
        consider(origin.x, -direction.x, 3);
    }
    if (direction.y > 0) {
        consider(side - origin.y, direction.y, 2);
    } else if (direction.y < 0) {
        consider(origin.y, -direction.y, 0);
    }

    const long long denominator = best_denominator;
    if (hit_side == 0 || hit_side == 2) {
        // x = origin.x + direction.x * t.
        const long long x_numerator =
            origin.x * denominator + direction.x * best_numerator;
        if (hit_side == 0) {
            return {x_numerator, denominator};
        }
        // Along the top edge the perimeter coordinate grows while x falls.
        return {3 * side * denominator - x_numerator, denominator};
    }

    // y = origin.y + direction.y * t.
    const long long y_numerator =
        origin.y * denominator + direction.y * best_numerator;
    if (hit_side == 1) {
        return {side * denominator + y_numerator, denominator};
    }
    // Along the left edge the perimeter coordinate grows while y falls.
    return {4 * side * denominator - y_numerator, denominator};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long side;
    int rock_count;
    cin >> side >> rock_count;

    Point observer;
    cin >> observer.x >> observer.y;

    const long long post_count = 4 * side;
    vector<pair<long long, long long>> blocked_intervals;
    blocked_intervals.reserve(2 * rock_count);

    const long double two_pi = 2.0L * acosl(-1.0L);

    for (int rock = 0; rock < rock_count; ++rock) {
        int vertex_count;
        cin >> vertex_count;

        struct Direction {
            Point vector;
            long double angle;
        };
        vector<Direction> directions;
        directions.reserve(vertex_count);

        for (int vertex = 0; vertex < vertex_count; ++vertex) {
            Point point;
            cin >> point.x >> point.y;
            Point direction{point.x - observer.x, point.y - observer.y};
            directions.push_back(
                {direction, atan2l(direction.y, direction.x)});
        }

        sort(directions.begin(), directions.end(),
             [](const Direction &first, const Direction &second) {
                 return first.angle < second.angle;
             });

        // Since the observer is outside a convex rock, all its viewing rays
        // fit in an angle strictly smaller than pi. Therefore the largest gap
        // between consecutive sorted rays is the outside gap. The rays just
        // after and before that gap are precisely the two tangents.
        int gap_after = 0;
        long double largest_gap = -1.0L;
        for (int index = 0; index < vertex_count; ++index) {
            const int next = (index + 1) % vertex_count;
            long double gap = directions[next].angle - directions[index].angle;
            if (next == 0) gap += two_pi;
            if (gap > largest_gap) {
                largest_gap = gap;
                gap_after = index;
            }
        }

        const Point start_direction =
            directions[(gap_after + 1) % vertex_count].vector;
        const Point end_direction = directions[gap_after].vector;
        Fraction start = perimeter_hit(side, observer, start_direction);
        Fraction end = perimeter_hit(side, observer, end_direction);

        // Unroll the circular interval so that end is counterclockwise after
        // start. Comparing fractions keeps tangent/fence-post coincidences
        // exact; such endpoint posts must count as blocked.
        if (end.numerator * start.denominator <
            start.numerator * end.denominator) {
            end.numerator += post_count * end.denominator;
        }

        long long first_post = ceil_fraction(start);
        long long last_post = floor_fraction(end);
        if (first_post > last_post) continue;  // No integer post in this cone.

        // Shift the unrolled interval to begin in [0, 4N), then split once if
        // it crosses the perimeter numbering cut.
        const long long turns = first_post / post_count;
        first_post -= turns * post_count;
        last_post -= turns * post_count;
        if (last_post < post_count) {
            blocked_intervals.push_back({first_post, last_post});
        } else {
            blocked_intervals.push_back({first_post, post_count - 1});
            blocked_intervals.push_back({0, last_post - post_count});
        }
    }

    sort(blocked_intervals.begin(), blocked_intervals.end());
    long long blocked_posts = 0;
    long long current_left = -1;
    long long current_right = -2;

    for (const auto &[left, right] : blocked_intervals) {
        if (left > current_right + 1) {
            if (current_left <= current_right) {
                blocked_posts += current_right - current_left + 1;
            }
            current_left = left;
            current_right = right;
        } else {
            current_right = max(current_right, right);
        }
    }
    if (current_left <= current_right) {
        blocked_posts += current_right - current_left + 1;
    }

    cout << post_count - blocked_posts << '\n';
    return 0;
}
