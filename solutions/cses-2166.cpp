#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

struct Node {
    long long sum = 0;
    long long best_prefix = 0;
};

// Concatenating a left interval L and a right interval R has two kinds of
// best prefix: one that ends inside L, or all of L followed by a prefix of R.
Node merge_nodes(const Node &left, const Node &right) {
    return {
        left.sum + right.sum,
        max(left.best_prefix, left.sum + right.best_prefix),
    };
}

class PrefixTree {
public:
    explicit PrefixTree(const vector<long long> &values)
        : size_(static_cast<int>(values.size())), tree_(4 * size_) {
        build(1, 0, size_ - 1, values);
    }

    void set_value(int index, long long value) {
        set_value(1, 0, size_ - 1, index, value);
    }

    Node query(int query_left, int query_right) const {
        return query(1, 0, size_ - 1, query_left, query_right);
    }

private:
    int size_;
    vector<Node> tree_;

    void build(int node, int left, int right,
               const vector<long long> &values) {
        if (left == right) {
            // Empty prefixes are allowed, so a negative leaf contributes a
            // best prefix of zero even though its full sum stays negative.
            tree_[node] = {values[left], max(0LL, values[left])};
            return;
        }

        const int middle = (left + right) / 2;
        build(node * 2, left, middle, values);
        build(node * 2 + 1, middle + 1, right, values);
        tree_[node] = merge_nodes(tree_[node * 2], tree_[node * 2 + 1]);
    }

    void set_value(int node, int left, int right,
                   int index, long long value) {
        if (left == right) {
            tree_[node] = {value, max(0LL, value)};
            return;
        }

        const int middle = (left + right) / 2;
        if (index <= middle) {
            set_value(node * 2, left, middle, index, value);
        } else {
            set_value(node * 2 + 1, middle + 1, right, index, value);
        }
        tree_[node] = merge_nodes(tree_[node * 2], tree_[node * 2 + 1]);
    }

    Node query(int node, int left, int right,
               int query_left, int query_right) const {
        if (query_right < left || right < query_left) {
            // {0,0} is a safe identity because every stored best prefix is at
            // least zero and is at least the interval's complete sum.
            return {};
        }
        if (query_left <= left && right <= query_right) {
            return tree_[node];
        }

        const int middle = (left + right) / 2;
        const Node left_answer = query(node * 2, left, middle,
                                       query_left, query_right);
        const Node right_answer = query(node * 2 + 1, middle + 1, right,
                                        query_left, query_right);

        // Order is essential: prefix summaries are not commutative. The left
        // answer must always be merged before the right answer.
        return merge_nodes(left_answer, right_answer);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int size, query_count;
    cin >> size >> query_count;

    vector<long long> values(size);
    for (long long &value : values) {
        cin >> value;
    }

    PrefixTree tree(values);
    while (query_count--) {
        int type, first, second;
        cin >> type >> first >> second;

        if (type == 1) {
            tree.set_value(first - 1, second);
        } else {
            cout << tree.query(first - 1, second - 1).best_prefix << '\n';
        }
    }

    return 0;
}
