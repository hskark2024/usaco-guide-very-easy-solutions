#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

// CEOI 2006: Antenna
//
// Binary-search the answer R. For a fixed R, anchor the candidate circle on
// each household A and rotate its center around A. Every other household B is
// covered during one angular interval; a radial event sweep finds whether K
// intervals overlap. A minimum covering circle always has a household on its
// boundary, so trying every anchor is sufficient.

struct Point {
    long double x;
    long double y;
};

struct Event {
    long double angle;
    bool entering;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int household_count;
    int required;
    cin >> household_count >> required;

    vector<Point> households(household_count);
    for (Point &point : households) cin >> point.x >> point.y;

    const long double pi = acosl(-1.0L);
    const long double two_pi = 2.0L * pi;

    auto feasible = [&](long double radius, Point *witness) {
        for (int anchor = 0; anchor < household_count; ++anchor) {
            vector<Event> events;
            events.reserve(4 * (household_count - 1));

            for (int other = 0; other < household_count; ++other) {
                if (other == anchor) continue;

                const long double dx = households[other].x - households[anchor].x;
                const long double dy = households[other].y - households[anchor].y;
                const long double distance = hypotl(dx, dy);

                // Two points can share a radius-R circle exactly when their
                // separation is at most its diameter.
                if (distance > 2.0L * radius + 1e-14L) continue;

                const long double direction = atan2l(dy, dx);
                const long double ratio =
                    min(1.0L, max(-1.0L, distance / (2.0L * radius)));
                const long double offset = acosl(ratio);

                long double start = direction - offset;
                while (start < 0.0L) start += two_pi;
                while (start >= two_pi) start -= two_pi;
                const long double finish = start + 2.0L * offset;

                // Duplicate every interval one full turn later. This removes
                // special cases for intervals that cross angle zero.
                events.push_back({start, true});
                events.push_back({finish, false});
                events.push_back({start + two_pi, true});
                events.push_back({finish + two_pi, false});
            }

            sort(events.begin(), events.end(), [](const Event &first,
                                                   const Event &second) {
                // Use an exact ordering relation here; an epsilon comparator
                // would not be transitive and could invalidate std::sort.
                if (first.angle != second.angle) {
                    return first.angle < second.angle;
                }
                // Closed disks include boundary points, so an entering event
                // must be counted before an exit at the same angle.
                return first.entering > second.entering;
            });

            int covered = 1;  // The anchor itself lies on every tested circle.
            for (const Event &event : events) {
                if (event.entering) {
                    ++covered;
                    if (covered >= required) {
                        if (witness != nullptr) {
                            witness->x = households[anchor].x +
                                         radius * cosl(event.angle);
                            witness->y = households[anchor].y +
                                         radius * sinl(event.angle);
                        }
                        return true;
                    }
                } else {
                    --covered;
                }
            }
        }
        return false;
    };

    // Centering at any household with this radius covers every household, so
    // the maximum pair distance is a simple guaranteed upper bound.
    long double high = 0.0L;
    for (int first = 0; first < household_count; ++first) {
        for (int second = first + 1; second < household_count; ++second) {
            high = max(high, hypotl(households[first].x - households[second].x,
                                    households[first].y - households[second].y));
        }
    }

    long double low = 0.0L;
    Point best_center{households[0].x, households[0].y};
    feasible(high, &best_center);

    // Eighty iterations are far beyond the 1e-4 output tolerance and leave
    // plenty of margin for coordinates up to 10000.
    for (int iteration = 0; iteration < 80; ++iteration) {
        const long double middle = (low + high) / 2.0L;
        Point candidate{};
        if (feasible(middle, &candidate)) {
            high = middle;
            best_center = candidate;
        } else {
            low = middle;
        }
    }

    cout << fixed << setprecision(10) << static_cast<double>(high) << '\n';
    cout << static_cast<double>(best_center.x) << ' '
         << static_cast<double>(best_center.y) << '\n';
    return 0;
}
