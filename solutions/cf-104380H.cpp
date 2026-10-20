#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct ReducedString {
    // After deleting every possible 01 pair, a binary string always has the
    // canonical form 111...000. We only need the counts of those unmatched
    // leading ones and trailing zeroes, not the remaining characters.
    int unmatched_ones = 0;
    int unmatched_zeroes = 0;
};

ReducedString concatenate(const ReducedString &left, const ReducedString &right) {
    // Each unmatched zero from the left can delete with one unmatched one
    // from the right. No other new pair crosses the concatenation boundary.
    const int new_pairs = min(left.unmatched_zeroes, right.unmatched_ones);
    return {
        left.unmatched_ones + right.unmatched_ones - new_pairs,
        left.unmatched_zeroes + right.unmatched_zeroes - new_pairs,
    };
}

class ReductionSegmentTree {
public:
    explicit ReductionSegmentTree(const string &bits) {
        leaf_count_ = 1;
        while (leaf_count_ < static_cast<int>(bits.size())) leaf_count_ *= 2;
        tree_.assign(2 * leaf_count_, ReducedString{});

        for (int index = 0; index < static_cast<int>(bits.size()); ++index) {
            tree_[leaf_count_ + index] = summary(bits[index]);
        }
        for (int node = leaf_count_ - 1; node >= 1; --node) {
            tree_[node] = concatenate(tree_[2 * node], tree_[2 * node + 1]);
        }
    }

    void flip(int index) {
        int node = leaf_count_ + index;

        // A real leaf has exactly one unmatched character, so swapping the
        // two counters is exactly the requested zero/one flip.
        swap(tree_[node].unmatched_ones, tree_[node].unmatched_zeroes);
        for (node /= 2; node >= 1; node /= 2) {
            tree_[node] = concatenate(tree_[2 * node], tree_[2 * node + 1]);
        }
    }

    ReducedString query(int left, int right) const {
        // Concatenation is associative but not commutative. Keep a forward
        // accumulator for nodes taken from the left and a backward accumulator
        // for nodes taken from the right, then join them in string order.
        ReducedString left_result;
        ReducedString right_result;
        for (left += leaf_count_, right += leaf_count_; left < right;
             left /= 2, right /= 2) {
            if (left & 1) {
                left_result = concatenate(left_result, tree_[left++]);
            }
            if (right & 1) {
                right_result = concatenate(tree_[--right], right_result);
            }
        }
        return concatenate(left_result, right_result);
    }

private:
    static ReducedString summary(char bit) {
        return bit == '1' ? ReducedString{1, 0} : ReducedString{0, 1};
    }

    int leaf_count_ = 1;
    vector<ReducedString> tree_;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string bits;
    cin >> bits;
    ReductionSegmentTree tree(bits);

    int operation_count;
    cin >> operation_count;
    while (operation_count--) {
        int type;
        cin >> type;
        if (type == 1) {
            int position;
            cin >> position;
            tree.flip(position - 1);
        } else {
            int left, right;
            cin >> left >> right;

            // The input range is inclusive and one-based; the tree interface
            // is half-open and zero-based, hence [left-1, right).
            const ReducedString answer = tree.query(left - 1, right);
            cout << answer.unmatched_ones + answer.unmatched_zeroes << '\n';
        }
    }
    return 0;
}
