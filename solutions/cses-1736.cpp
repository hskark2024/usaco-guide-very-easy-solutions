#include <iostream>
#include <vector>
using namespace std;

// Each update adds 1, 2, 3, ... across its chosen interval.  At absolute
// position i, an update starting at ql adds i - ql + 1.  That is an affine
// function of i: 1*i + (1-ql).  A lazy node therefore stores a slope and an
// intercept instead of expanding the progression element by element.
class AffineLazySegmentTree {
public:
    explicit AffineLazySegmentTree(const vector<long long> &values)
        : size_(static_cast<int>(values.size())),
          sum_(4 * size_, 0),
          lazy_slope_(4 * size_, 0),
          lazy_intercept_(4 * size_, 0) {
        build(1, 0, size_ - 1, values);
    }

    void add_progression(int query_left, int query_right) {
        // With zero-based positions, the desired increment is
        // position - query_left + 1.
        update(1, 0, size_ - 1, query_left, query_right,
               1, 1LL - query_left);
    }

    long long range_sum(int query_left, int query_right) {
        return query(1, 0, size_ - 1, query_left, query_right);
    }

private:
    int size_;
    vector<long long> sum_;
    vector<long long> lazy_slope_;
    vector<long long> lazy_intercept_;

    static long long index_sum(int left, int right) {
        // Sum left + (left+1) + ... + right without an O(length) loop.
        const long long length = right - left + 1LL;
        return (left + right) * length / 2;
    }

    void build(int node, int left, int right,
               const vector<long long> &values) {
        if (left == right) {
            sum_[node] = values[left];
            return;
        }

        const int middle = (left + right) / 2;
        build(node * 2, left, middle, values);
        build(node * 2 + 1, middle + 1, right, values);
        pull(node);
    }

    void pull(int node) {
        sum_[node] = sum_[node * 2] + sum_[node * 2 + 1];
    }

    void apply(int node, int left, int right,
               long long slope, long long intercept) {
        // Sum (slope*i + intercept) over every absolute index in this node.
        const long long length = right - left + 1LL;
        sum_[node] += slope * index_sum(left, right) + intercept * length;

        // Affine additions commute, so pending coefficients simply add.
        lazy_slope_[node] += slope;
        lazy_intercept_[node] += intercept;
    }

    void push(int node, int left, int right) {
        if (left == right
            || (lazy_slope_[node] == 0 && lazy_intercept_[node] == 0)) {
            return;
        }

        const int middle = (left + right) / 2;
        apply(node * 2, left, middle,
              lazy_slope_[node], lazy_intercept_[node]);
        apply(node * 2 + 1, middle + 1, right,
              lazy_slope_[node], lazy_intercept_[node]);

        // The children now remember this work, so clear the parent's tag.
        lazy_slope_[node] = 0;
        lazy_intercept_[node] = 0;
    }

    void update(int node, int left, int right,
                int query_left, int query_right,
                long long slope, long long intercept) {
        if (query_right < left || right < query_left) {
            return;
        }
        if (query_left <= left && right <= query_right) {
            apply(node, left, right, slope, intercept);
            return;
        }

        push(node, left, right);
        const int middle = (left + right) / 2;
        update(node * 2, left, middle,
               query_left, query_right, slope, intercept);
        update(node * 2 + 1, middle + 1, right,
               query_left, query_right, slope, intercept);
        pull(node);
    }

    long long query(int node, int left, int right,
                    int query_left, int query_right) {
        if (query_right < left || right < query_left) {
            return 0;
        }
        if (query_left <= left && right <= query_right) {
            return sum_[node];
        }

        push(node, left, right);
        const int middle = (left + right) / 2;
        return query(node * 2, left, middle, query_left, query_right)
               + query(node * 2 + 1, middle + 1, right,
                       query_left, query_right);
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

    AffineLazySegmentTree tree(values);

    for (int query = 0; query < query_count; ++query) {
        int type, left, right;
        cin >> type >> left >> right;

        // Convert the official one-based inclusive endpoints to zero-based.
        --left;
        --right;

        if (type == 1) {
            tree.add_progression(left, right);
        } else {
            cout << tree.range_sum(left, right) << '\n';
        }
    }

    return 0;
}
