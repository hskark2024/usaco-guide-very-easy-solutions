#include <iostream>
#include <vector>
using namespace std;

// Point updates and prefix counts let the offline sweep count points inside
// every query rectangle in O(log n) time per event.
class FenwickTree {
public:
    explicit FenwickTree(int size) : tree_(size + 1, 0) {}

    void add(int position, int delta) {
        // Positions are already one-based because permutation indices are
        // naturally numbered from 1 through N.
        for (int index = position;
             index < static_cast<int>(tree_.size());
             index += index & -index) {
            tree_[index] += delta;
        }
    }

    int prefix_sum(int position) const {
        int total = 0;
        for (int index = position; index > 0; index -= index & -index) {
            total += tree_[index];
        }
        return total;
    }

    int range_sum(int left, int right) const {
        return prefix_sum(right) - prefix_sum(left - 1);
    }

private:
    vector<int> tree_;
};

struct QueryEvent {
    int first_array_left;
    int first_array_right;
    int query_index;
    int sign;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int permutation_size;
    cin >> permutation_size;

    // position_in_first[value] converts a value into its y-coordinate in the
    // first permutation. Values are unique, so this is a true inverse map.
    vector<int> position_in_first(permutation_size + 1);
    for (int position = 1; position <= permutation_size; ++position) {
        int value;
        cin >> value;
        position_in_first[value] = position;
    }

    // At x = position in the second permutation, store y = position of the
    // same value in the first permutation. Every value becomes one 2D point.
    vector<int> first_position_at_second_position(permutation_size + 1);
    for (int position = 1; position <= permutation_size; ++position) {
        int value;
        cin >> value;
        first_position_at_second_position[position] = position_in_first[value];
    }

    int query_count;
    cin >> query_count;

    // A rectangle count on second positions [L2, R2] is a difference of two
    // sweep prefixes: prefix(R2) - prefix(L2 - 1). Store both signed events.
    vector<vector<QueryEvent>> events_at_prefix(permutation_size + 1);
    vector<int> requested_length(query_count);
    vector<int> common_value_count(query_count, 0);

    for (int query = 0; query < query_count; ++query) {
        int first_left, first_right, second_left, second_right;
        cin >> first_left >> first_right >> second_left >> second_right;

        requested_length[query] = first_right - first_left + 1;
        events_at_prefix[second_right].push_back(
            {first_left, first_right, query, +1});
        events_at_prefix[second_left - 1].push_back(
            {first_left, first_right, query, -1});
    }

    FenwickTree seen_first_positions(permutation_size);

    // Sweep through prefixes of the second permutation. After inserting x,
    // the Fenwick tree contains exactly the y-coordinates for points with
    // second-permutation position at most x.
    for (int second_prefix = 0;
         second_prefix <= permutation_size;
         ++second_prefix) {
        if (second_prefix > 0) {
            seen_first_positions.add(
                first_position_at_second_position[second_prefix], 1);
        }

        for (const QueryEvent &event : events_at_prefix[second_prefix]) {
            const int points_in_first_range = seen_first_positions.range_sum(
                event.first_array_left,
                event.first_array_right);
            common_value_count[event.query_index] +=
                event.sign * points_in_first_range;
        }
    }

    for (int query = 0; query < query_count; ++query) {
        // Every common value may stay. Each missing target value needs one
        // swap with an unwanted value inside the first subarray, so the exact
        // minimum is length minus the size of the set intersection.
        cout << requested_length[query] - common_value_count[query] << '\n';
    }
    return 0;
}
