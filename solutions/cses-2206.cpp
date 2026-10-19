#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>
using namespace std;

struct PriceNode {
    long long minimum_minus_index;
    long long minimum_plus_index;
};

PriceNode combine(const PriceNode &left, const PriceNode &right) {
    return {
        min(left.minimum_minus_index, right.minimum_minus_index),
        min(left.minimum_plus_index, right.minimum_plus_index),
    };
}

class PizzeriaSegmentTree {
public:
    explicit PizzeriaSegmentTree(const vector<long long> &prices) {
        leaf_count_ = 1;
        while (leaf_count_ < static_cast<int>(prices.size())) {
            leaf_count_ *= 2;
        }

        const long long infinity = numeric_limits<long long>::max() / 4;
        tree_.assign(2 * leaf_count_, {infinity, infinity});
        for (int index = 0; index < static_cast<int>(prices.size()); ++index) {
            tree_[leaf_count_ + index] = make_leaf(index, prices[index]);
        }
        for (int node = leaf_count_ - 1; node >= 1; --node) {
            tree_[node] = combine(tree_[2 * node], tree_[2 * node + 1]);
        }
    }

    void update(int index, long long price) {
        int node = leaf_count_ + index;
        tree_[node] = make_leaf(index, price);
        for (node /= 2; node >= 1; node /= 2) {
            tree_[node] = combine(tree_[2 * node], tree_[2 * node + 1]);
        }
    }

    long long cheapest_delivery(int customer_index) const {
        // For a source i on the left, p[i] + |i-k| becomes
        // (p[i]-i) + k. On the right it becomes (p[i]+i) - k.
        const PriceNode left_sources = query(0, customer_index + 1);
        const PriceNode right_sources = query(customer_index, leaf_count_);
        return min(left_sources.minimum_minus_index + customer_index,
                   right_sources.minimum_plus_index - customer_index);
    }

private:
    static PriceNode make_leaf(int index, long long price) {
        return {price - index, price + index};
    }

    PriceNode query(int left, int right) const {
        const long long infinity = numeric_limits<long long>::max() / 4;
        PriceNode result{infinity, infinity};
        left += leaf_count_;
        right += leaf_count_;

        // Minimum is commutative, so a single accumulator is sufficient.
        while (left < right) {
            if (left & 1) result = combine(result, tree_[left++]);
            if (right & 1) result = combine(result, tree_[--right]);
            left /= 2;
            right /= 2;
        }
        return result;
    }

    int leaf_count_ = 1;
    vector<PriceNode> tree_;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int building_count, query_count;
    cin >> building_count >> query_count;
    vector<long long> prices(building_count);
    for (long long &price : prices) cin >> price;

    PizzeriaSegmentTree tree(prices);
    while (query_count--) {
        int type, one_based_index;
        cin >> type >> one_based_index;
        const int index = one_based_index - 1;

        if (type == 1) {
            long long new_price;
            cin >> new_price;
            tree.update(index, new_price);
        } else {
            cout << tree.cheapest_delivery(index) << '\n';
        }
    }

    return 0;
}
