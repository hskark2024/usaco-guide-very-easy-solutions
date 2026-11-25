#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

// CSES 1619: Restaurant Customers
//
// Turn every visit into two chronological events: +1 at arrival and -1 at
// departure.  Sweeping the events from left to right keeps exactly the number
// of customers currently inside.  The maximum running total is the answer.

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int customer_count;
    cin >> customer_count;

    vector<pair<long long, int>> events;
    events.reserve(2 * customer_count);
    for (int customer = 0; customer < customer_count; ++customer) {
        long long arrival, departure;
        cin >> arrival >> departure;

        // Positive means one customer enters; negative means one leaves.
        events.push_back({arrival, +1});
        events.push_back({departure, -1});
    }

    // The official task guarantees distinct event times.  The second field
    // still gives sensible half-open interval behavior for a tied timestamp:
    // departures (-1) would be processed before arrivals (+1).
    sort(events.begin(), events.end());

    int currently_inside = 0;
    int maximum_inside = 0;
    for (const auto &[time, change] : events) {
        (void)time;  // The ordering matters; the numeric value is no longer needed.
        currently_inside += change;
        maximum_inside = max(maximum_inside, currently_inside);
    }

    cout << maximum_inside << '\n';
    return 0;
}
