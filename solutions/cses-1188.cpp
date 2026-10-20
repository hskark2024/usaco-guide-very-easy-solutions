#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct RunSummary {
    int length = 0;
    int prefix_length = 0;
    int suffix_length = 0;
    int best_length = 0;
    char first_bit = '?';
    char last_bit = '?';
};

RunSummary combine(const RunSummary &left, const RunSummary &right) {
    // An empty padded interval is the identity. This also makes iterative
    // range-combining safe even though today's answer only needs the root.
    if (left.length == 0) return right;
    if (right.length == 0) return left;

    RunSummary result;
    result.length = left.length + right.length;
    result.first_bit = left.first_bit;
    result.last_bit = right.last_bit;

    // A run crosses the boundary precisely when the touching bits agree.
    // In that case the two boundary runs become one longer run.
    const bool joins = (left.last_bit == right.first_bit);
    const int crossing = joins ? left.suffix_length + right.prefix_length : 0;
    result.best_length = max({left.best_length, right.best_length, crossing});

    // The combined prefix normally stops inside the left child. It may absorb
    // the right prefix only if the ENTIRE left interval is one matching run.
    result.prefix_length = left.prefix_length;
    if (joins && left.prefix_length == left.length) {
        result.prefix_length += right.prefix_length;
    }

    // The suffix is symmetric: it extends left only when all of the right
    // child belongs to the same boundary run.
    result.suffix_length = right.suffix_length;
    if (joins && right.suffix_length == right.length) {
        result.suffix_length += left.suffix_length;
    }
    return result;
}

class RunSegmentTree {
public:
    explicit RunSegmentTree(const string &bits) {
        leaf_count_ = 1;
        while (leaf_count_ < static_cast<int>(bits.size())) leaf_count_ *= 2;
        tree_.assign(2 * leaf_count_, RunSummary{});

        for (int index = 0; index < static_cast<int>(bits.size()); ++index) {
            // One bit is simultaneously the prefix, suffix, and best run of
            // its one-character interval.
            tree_[leaf_count_ + index] = {1, 1, 1, 1, bits[index], bits[index]};
        }
        for (int node = leaf_count_ - 1; node >= 1; --node) {
            tree_[node] = combine(tree_[2 * node], tree_[2 * node + 1]);
        }
    }

    void flip(int index) {
        int node = leaf_count_ + index;

        // Only the leaf's bit changes. Its four run lengths remain one.
        tree_[node].first_bit = (tree_[node].first_bit == '0' ? '1' : '0');
        tree_[node].last_bit = tree_[node].first_bit;

        // Rebuilding this root path refreshes every interval containing the
        // changed position; all disjoint segment-tree nodes remain correct.
        for (node /= 2; node >= 1; node /= 2) {
            tree_[node] = combine(tree_[2 * node], tree_[2 * node + 1]);
        }
    }

    int longest_run() const {
        // The root represents the whole real string because padded leaves are
        // empty identities and therefore cannot create artificial runs.
        return tree_[1].best_length;
    }

private:
    int leaf_count_ = 1;
    vector<RunSummary> tree_;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string bits;
    cin >> bits;

    RunSegmentTree tree(bits);
    int change_count;
    cin >> change_count;
    for (int change = 0; change < change_count; ++change) {
        int one_based_position;
        cin >> one_based_position;
        tree.flip(one_based_position - 1);
        cout << tree.longest_run() << (change + 1 == change_count ? '\n' : ' ');
    }
    return 0;
}
