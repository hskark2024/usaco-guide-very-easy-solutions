#include <algorithm>
#include <cstdio>
#include <iostream>
#include <limits>
#include <vector>
using namespace std;

// This lazy segment tree keeps two summaries for every interval:
//   1. the minimum field value, and
//   2. the total number of haybales.
// A range increment changes both summaries in constant time for a full node.
class HaybaleTree {
public:
    explicit HaybaleTree(const vector<long long> &values)
        : size_(static_cast<int>(values.size())),
          minimum_(4 * size_, 0),
          sum_(4 * size_, 0),
          lazy_add_(4 * size_, 0) {
        build(1, 0, size_ - 1, values);
    }

    void add_range(int query_left, int query_right, long long amount) {
        add_range(1, 0, size_ - 1, query_left, query_right, amount);
    }

    long long range_minimum(int query_left, int query_right) {
        return range_minimum(1, 0, size_ - 1, query_left, query_right);
    }

    long long range_sum(int query_left, int query_right) {
        return range_sum(1, 0, size_ - 1, query_left, query_right);
    }

private:
    int size_;
    vector<long long> minimum_;
    vector<long long> sum_;
    vector<long long> lazy_add_;

    void build(int node, int left, int right,
               const vector<long long> &values) {
        if (left == right) {
            minimum_[node] = sum_[node] = values[left];
            return;
        }

        const int middle = (left + right) / 2;
        build(node * 2, left, middle, values);
        build(node * 2 + 1, middle + 1, right, values);
        pull(node);
    }

    void pull(int node) {
        minimum_[node] = min(minimum_[node * 2], minimum_[node * 2 + 1]);
        sum_[node] = sum_[node * 2] + sum_[node * 2 + 1];
    }

    void apply_add(int node, int left, int right, long long amount) {
        // Every element grows by amount, so the minimum grows by amount and
        // the total grows by amount times the number of elements.
        minimum_[node] += amount;
        sum_[node] += amount * (right - left + 1LL);
        lazy_add_[node] += amount;
    }

    void push(int node, int left, int right) {
        if (left == right || lazy_add_[node] == 0) {
            return;
        }

        const int middle = (left + right) / 2;
        apply_add(node * 2, left, middle, lazy_add_[node]);
        apply_add(node * 2 + 1, middle + 1, right, lazy_add_[node]);
        lazy_add_[node] = 0;
    }

    void add_range(int node, int left, int right,
                   int query_left, int query_right, long long amount) {
        if (query_right < left || right < query_left) {
            return;
        }
        if (query_left <= left && right <= query_right) {
            apply_add(node, left, right, amount);
            return;
        }

        push(node, left, right);
        const int middle = (left + right) / 2;
        add_range(node * 2, left, middle,
                  query_left, query_right, amount);
        add_range(node * 2 + 1, middle + 1, right,
                  query_left, query_right, amount);
        pull(node);
    }

    long long range_minimum(int node, int left, int right,
                            int query_left, int query_right) {
        if (query_right < left || right < query_left) {
            return numeric_limits<long long>::max();
        }
        if (query_left <= left && right <= query_right) {
            return minimum_[node];
        }

        push(node, left, right);
        const int middle = (left + right) / 2;
        return min(range_minimum(node * 2, left, middle,
                                 query_left, query_right),
                   range_minimum(node * 2 + 1, middle + 1, right,
                                 query_left, query_right));
    }

    long long range_sum(int node, int left, int right,
                        int query_left, int query_right) {
        if (query_right < left || right < query_left) {
            return 0;
        }
        if (query_left <= left && right <= query_right) {
            return sum_[node];
        }

        push(node, left, right);
        const int middle = (left + right) / 2;
        return range_sum(node * 2, left, middle,
                         query_left, query_right)
               + range_sum(node * 2 + 1, middle + 1, right,
                           query_left, query_right);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Preserve USACO file behavior while still allowing stdin/stdout tests.
    if (FILE *input_file = fopen("haybales.in", "r")) {
        fclose(input_file);
        freopen("haybales.in", "r", stdin);
        freopen("haybales.out", "w", stdout);
    }

    int field_count, query_count;
    cin >> field_count >> query_count;

    vector<long long> haybales(field_count);
    for (long long &count : haybales) {
        cin >> count;
    }

    HaybaleTree tree(haybales);
    while (query_count--) {
        char operation;
        int left, right;
        cin >> operation >> left >> right;
        --left;
        --right;

        if (operation == 'P') {
            long long amount;
            cin >> amount;
            tree.add_range(left, right, amount);
        } else if (operation == 'M') {
            cout << tree.range_minimum(left, right) << '\n';
        } else {
            cout << tree.range_sum(left, right) << '\n';
        }
    }

    return 0;
}
