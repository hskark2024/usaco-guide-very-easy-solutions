#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
using namespace std;

using int64 = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int64 initial_fall_time, operation_time;
    cin >> initial_fall_time >> operation_time;

    auto arrival_time = [&](int64 operation_count) -> long double {
        // After x operations, gravity is x + 1.  The total time is the time
        // spent powering up plus the shortened fall time.
        return static_cast<long double>(operation_time) * operation_count
               + static_cast<long double>(initial_fall_time)
                     / sqrtl(static_cast<long double>(operation_count) + 1.0L);
    };

    // Performing x operations already costs B*x.  Doing nothing costs A, so
    // no optimum can lie beyond floor(A/B).  This gives a finite integer
    // search interval even though the statement allows unlimited operations.
    int64 left = 0;
    int64 right = initial_fall_time / operation_time;

    // f(x) = B*x + A/sqrt(x+1) is convex: the falling-time improvement gets
    // smaller with every operation while each operation always costs B.
    // Integer ternary search repeatedly discards the outer third that cannot
    // contain the minimum.  We stop with a tiny interval and inspect every
    // remaining integer, which safely handles a flat or boundary minimum.
    while (right - left > 8) {
        const int64 first_third = left + (right - left) / 3;
        const int64 second_third = right - (right - left) / 3;

        if (arrival_time(first_third) <= arrival_time(second_third)) {
            right = second_third - 1;
        } else {
            left = first_third + 1;
        }
    }

    long double answer = arrival_time(left);
    for (int64 operations = left + 1; operations <= right; ++operations) {
        answer = min(answer, arrival_time(operations));
    }

    cout << fixed << setprecision(15) << answer << '\n';
    return 0;
}
