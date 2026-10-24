#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

// A Fenwick tree stores how many currently active vertical segments have each
// compressed x-coordinate. Both updates and prefix sums take O(log n) time.
class FenwickTree {
public:
    explicit FenwickTree(int coordinate_count)
        : tree_(coordinate_count + 1, 0) {}

    void add(int zero_based_index, int delta) {
        // Fenwick internals are one-based, so shift the compressed index once.
        for (int index = zero_based_index + 1;
             index < static_cast<int>(tree_.size());
             index += index & -index) {
            tree_[index] += delta;
        }
    }

    int prefix_sum(int count) const {
        // Return the sum of compressed indices [0, count). Passing a count
        // instead of an inclusive endpoint makes empty prefixes convenient.
        int total = 0;
        for (int index = count; index > 0; index -= index & -index) {
            total += tree_[index];
        }
        return total;
    }

private:
    vector<int> tree_;
};

enum EventType {
    ADD_VERTICAL = 0,
    QUERY_HORIZONTAL = 1,
    REMOVE_VERTICAL = 2,
};

struct Event {
    int y;
    EventType type;
    int left_x;
    int right_x;

    bool operator<(const Event &other) const {
        if (y != other.y) return y < other.y;
        // Start, query, then end makes the geometric interval inclusive. The
        // official input promises that an endpoint is never an intersection,
        // but this order also documents the intended boundary convention.
        return type < other.type;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int segment_count;
    cin >> segment_count;

    vector<Event> events;
    events.reserve(2 * segment_count);

    // Only vertical x-coordinates ever receive Fenwick updates. Compressing
    // just those coordinates avoids depending on the +/- 1,000,000 bound.
    vector<int> vertical_x_coordinates;
    vertical_x_coordinates.reserve(segment_count);

    for (int segment = 0; segment < segment_count; ++segment) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;

        if (y1 == y2) {
            // A horizontal segment asks how many active vertical x-values lie
            // in its inclusive x-range at this sweep height.
            if (x1 > x2) swap(x1, x2);
            events.push_back({y1, QUERY_HORIZONTAL, x1, x2});
        } else {
            // A vertical segment becomes active at its lower endpoint and is
            // removed at its upper endpoint.
            if (y1 > y2) swap(y1, y2);
            events.push_back({y1, ADD_VERTICAL, x1, x1});
            events.push_back({y2, REMOVE_VERTICAL, x1, x1});
            vertical_x_coordinates.push_back(x1);
        }
    }

    sort(events.begin(), events.end());
    sort(vertical_x_coordinates.begin(), vertical_x_coordinates.end());
    vertical_x_coordinates.erase(
        unique(vertical_x_coordinates.begin(), vertical_x_coordinates.end()),
        vertical_x_coordinates.end());

    FenwickTree active_verticals(
        static_cast<int>(vertical_x_coordinates.size()));
    long long intersection_count = 0;

    for (const Event &event : events) {
        if (event.type == QUERY_HORIZONTAL) {
            // lower_bound gives the first stored x inside the range;
            // upper_bound gives one past the final stored x inside the range.
            const int first = static_cast<int>(lower_bound(
                vertical_x_coordinates.begin(),
                vertical_x_coordinates.end(),
                event.left_x) - vertical_x_coordinates.begin());
            const int after_last = static_cast<int>(upper_bound(
                vertical_x_coordinates.begin(),
                vertical_x_coordinates.end(),
                event.right_x) - vertical_x_coordinates.begin());

            intersection_count +=
                active_verticals.prefix_sum(after_last)
                - active_verticals.prefix_sum(first);
        } else {
            const int compressed_x = static_cast<int>(lower_bound(
                vertical_x_coordinates.begin(),
                vertical_x_coordinates.end(),
                event.left_x) - vertical_x_coordinates.begin());

            // Adding marks the vertical segment active; removing undoes the
            // exact same contribution when the sweep reaches its top.
            active_verticals.add(
                compressed_x,
                event.type == ADD_VERTICAL ? 1 : -1);
        }
    }

    cout << intersection_count << '\n';
    return 0;
}
