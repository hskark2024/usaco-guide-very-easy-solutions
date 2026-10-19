#include <iostream>
#include <vector>
using namespace std;

constexpr long long MOD = 998244353;

struct AffineFunction {
    long long multiplier = 1;
    long long constant = 0;
};

// Return second(first(x)). The order is deliberately left-to-right rather
// than commutative: an interval stores the functions in the exact order in
// which the query applies them.
AffineFunction concatenate(const AffineFunction &first,
                           const AffineFunction &second) {
    return {
        second.multiplier * first.multiplier % MOD,
        (second.multiplier * first.constant + second.constant) % MOD,
    };
}

class CompositionSegmentTree {
public:
    explicit CompositionSegmentTree(const vector<AffineFunction> &functions) {
        // Padding leaves hold f(x)=x, the identity for composition.
        leaf_count_ = 1;
        while (leaf_count_ < static_cast<int>(functions.size())) {
            leaf_count_ *= 2;
        }
        tree_.assign(2 * leaf_count_, AffineFunction{});
        for (int index = 0; index < static_cast<int>(functions.size()); ++index) {
            tree_[leaf_count_ + index] = functions[index];
        }
        for (int node = leaf_count_ - 1; node >= 1; --node) {
            tree_[node] = concatenate(tree_[2 * node], tree_[2 * node + 1]);
        }
    }

    void set_function(int index, AffineFunction replacement) {
        int node = leaf_count_ + index;
        tree_[node] = replacement;

        // Only ancestors of the replaced leaf can change.
        for (node /= 2; node >= 1; node /= 2) {
            tree_[node] = concatenate(tree_[2 * node], tree_[2 * node + 1]);
        }
    }

    AffineFunction query(int left, int right) const {
        // These two accumulators are necessary because composition is not
        // commutative. left_result grows toward the right, while right_result
        // grows toward the left. They meet in the correct array order.
        AffineFunction left_result;
        AffineFunction right_result;
        left += leaf_count_;
        right += leaf_count_;

        while (left < right) {
            if (left & 1) {
                left_result = concatenate(left_result, tree_[left++]);
            }
            if (right & 1) {
                right_result = concatenate(tree_[--right], right_result);
            }
            left /= 2;
            right /= 2;
        }
        return concatenate(left_result, right_result);
    }

private:
    int leaf_count_ = 1;
    vector<AffineFunction> tree_;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int function_count, query_count;
    cin >> function_count >> query_count;

    vector<AffineFunction> functions(function_count);
    for (AffineFunction &function : functions) {
        cin >> function.multiplier >> function.constant;
    }

    CompositionSegmentTree tree(functions);
    for (int query_index = 0; query_index < query_count; ++query_index) {
        int type, first, second;
        long long third;
        cin >> type >> first >> second >> third;

        if (type == 0) {
            // Replace f_first(x) with second*x + third.
            tree.set_function(first, {second, third});
        } else {
            // Apply f_first, ..., f_(second-1) to third.
            const AffineFunction combined = tree.query(first, second);
            cout << (combined.multiplier * third + combined.constant) % MOD << '\n';
        }
    }

    return 0;
}
