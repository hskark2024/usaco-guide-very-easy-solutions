#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

struct Operation {
    char type;
    int argument;
};

class FenwickTree {
public:
    explicit FenwickTree(int size) : tree_(size + 1, 0) {}

    void add(int index, int delta) {
        // Fenwick indices are one-based. Each visited node owns a range whose
        // length is its lowest set bit.
        for (; index < static_cast<int>(tree_.size()); index += index & -index) {
            tree_[index] += delta;
        }
    }

    int prefix_sum(int index) const {
        int total = 0;
        for (; index > 0; index -= index & -index) {
            total += tree_[index];
        }
        return total;
    }

    int kth_index(int order) const {
        // Binary lifting constructs the largest Fenwick index whose prefix
        // contains fewer than order present values. The answer is next.
        int index = 0;
        int accumulated = 0;
        int jump = 1;
        while (2 * jump < static_cast<int>(tree_.size())) {
            jump *= 2;
        }
        for (; jump > 0; jump /= 2) {
            const int candidate = index + jump;
            if (candidate < static_cast<int>(tree_.size()) &&
                accumulated + tree_[candidate] < order) {
                index = candidate;
                accumulated += tree_[candidate];
            }
        }
        return index + 1;
    }

private:
    vector<int> tree_;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int query_count;
    cin >> query_count;

    vector<Operation> operations(query_count);
    vector<int> coordinates;
    coordinates.reserve(query_count);
    for (Operation &operation : operations) {
        cin >> operation.type >> operation.argument;
        // Only value-based commands contribute coordinates. K's argument is
        // a rank, not a possible set value.
        if (operation.type != 'K') {
            coordinates.push_back(operation.argument);
        }
    }

    sort(coordinates.begin(), coordinates.end());
    coordinates.erase(unique(coordinates.begin(), coordinates.end()),
                      coordinates.end());

    FenwickTree present_count(static_cast<int>(coordinates.size()));
    vector<bool> present(coordinates.size(), false);

    for (const Operation &operation : operations) {
        if (operation.type == 'K') {
            const int set_size = present_count.prefix_sum(
                static_cast<int>(coordinates.size())
            );
            if (operation.argument > set_size) {
                cout << "invalid\n";
            } else {
                const int compressed = present_count.kth_index(operation.argument);
                cout << coordinates[compressed - 1] << '\n';
            }
            continue;
        }

        const int zero_based = static_cast<int>(
            lower_bound(coordinates.begin(), coordinates.end(), operation.argument)
            - coordinates.begin()
        );

        if (operation.type == 'I') {
            // Set semantics: inserting an existing value changes nothing.
            if (!present[zero_based]) {
                present[zero_based] = true;
                present_count.add(zero_based + 1, 1);
            }
        } else if (operation.type == 'D') {
            // Likewise, deleting a missing value is a no-op.
            if (present[zero_based]) {
                present[zero_based] = false;
                present_count.add(zero_based + 1, -1);
            }
        } else {
            // lower_bound points at the first coordinate >= x. Therefore the
            // prefix strictly before it counts exactly the values below x.
            cout << present_count.prefix_sum(zero_based) << '\n';
        }
    }

    return 0;
}
