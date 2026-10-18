#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

class MaximumSegmentTree {
public:
    explicit MaximumSegmentTree(const vector<long long> &values) {
        // A power-of-two base makes parent/child arithmetic simple. Unused
        // leaves stay zero because every request and capacity is positive.
        leaf_count_ = 1;
        while (leaf_count_ < static_cast<int>(values.size())) {
            leaf_count_ *= 2;
        }
        tree_.assign(2 * leaf_count_, 0);
        for (int index = 0; index < static_cast<int>(values.size()); ++index) {
            tree_[leaf_count_ + index] = values[index];
        }
        for (int node = leaf_count_ - 1; node >= 1; --node) {
            tree_[node] = max(tree_[2 * node], tree_[2 * node + 1]);
        }
    }

    int reserve_first(long long rooms_needed) {
        // The root stores the best capacity anywhere. If even it is too
        // small, no hotel can accept this group.
        if (tree_[1] < rooms_needed) {
            return -1;
        }

        int node = 1;
        while (node < leaf_count_) {
            // Prefer the left child whenever it contains a valid hotel. This
            // greedy descent is what guarantees the smallest hotel index.
            if (tree_[2 * node] >= rooms_needed) {
                node = 2 * node;
            } else {
                node = 2 * node + 1;
            }
        }

        // Consume the rooms at the chosen leaf, then repair all maxima on
        // the path back to the root.
        tree_[node] -= rooms_needed;
        for (int parent = node / 2; parent >= 1; parent /= 2) {
            tree_[parent] = max(tree_[2 * parent], tree_[2 * parent + 1]);
        }
        return node - leaf_count_;
    }

private:
    int leaf_count_ = 1;
    vector<long long> tree_;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int hotel_count, group_count;
    cin >> hotel_count >> group_count;

    vector<long long> free_rooms(hotel_count);
    for (long long &rooms : free_rooms) {
        cin >> rooms;
    }

    MaximumSegmentTree hotels(free_rooms);
    for (int group = 0; group < group_count; ++group) {
        long long rooms_needed;
        cin >> rooms_needed;
        const int zero_based_hotel = hotels.reserve_first(rooms_needed);
        cout << (zero_based_hotel == -1 ? 0 : zero_based_hotel + 1)
             << (group + 1 == group_count ? '\n' : ' ');
    }

    return 0;
}
