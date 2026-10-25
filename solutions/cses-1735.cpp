#include <iostream>
#include <vector>
using namespace std;

// This lazy segment tree supports both range assignment and range addition.
// Their order matters: an assignment erases every older pending update, while
// a later addition must be applied on top of the assigned value.
class LazySegmentTree {
public:
    explicit LazySegmentTree(const vector<long long> &values)
        : size_(static_cast<int>(values.size())),
          sum_(4 * size_, 0),
          pending_add_(4 * size_, 0),
          pending_set_(4 * size_, 0),
          has_pending_set_(4 * size_, false) {
        build(1, 0, size_ - 1, values);
    }

    void add_range(int query_left, int query_right, long long value) {
        update_add(1, 0, size_ - 1, query_left, query_right, value);
    }

    void set_range(int query_left, int query_right, long long value) {
        update_set(1, 0, size_ - 1, query_left, query_right, value);
    }

    long long range_sum(int query_left, int query_right) {
        return query(1, 0, size_ - 1, query_left, query_right);
    }

private:
    int size_;
    vector<long long> sum_;
    vector<long long> pending_add_;
    vector<long long> pending_set_;
    vector<bool> has_pending_set_;

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

    void apply_set(int node, int left, int right, long long value) {
        const long long length = right - left + 1LL;
        sum_[node] = value * length;

        // This assignment replaces every older operation for the node.
        has_pending_set_[node] = true;
        pending_set_[node] = value;
        pending_add_[node] = 0;
    }

    void apply_add(int node, int left, int right, long long value) {
        const long long length = right - left + 1LL;
        sum_[node] += value * length;

        if (has_pending_set_[node]) {
            // set(x), then add(y) is equivalent to one set(x+y).
            pending_set_[node] += value;
        } else {
            pending_add_[node] += value;
        }
    }

    void push(int node, int left, int right) {
        if (left == right) {
            return;
        }

        const int middle = (left + right) / 2;

        // Assignment must travel first because it wipes out older child tags.
        if (has_pending_set_[node]) {
            apply_set(node * 2, left, middle, pending_set_[node]);
            apply_set(node * 2 + 1, middle + 1, right,
                      pending_set_[node]);
            has_pending_set_[node] = false;
        }

        // Any addition stored on this node happened after its assignment.
        if (pending_add_[node] != 0) {
            apply_add(node * 2, left, middle, pending_add_[node]);
            apply_add(node * 2 + 1, middle + 1, right,
                      pending_add_[node]);
            pending_add_[node] = 0;
        }
    }

    void update_add(int node, int left, int right,
                    int query_left, int query_right, long long value) {
        if (query_right < left || right < query_left) {
            return;
        }
        if (query_left <= left && right <= query_right) {
            apply_add(node, left, right, value);
            return;
        }

        push(node, left, right);
        const int middle = (left + right) / 2;
        update_add(node * 2, left, middle,
                   query_left, query_right, value);
        update_add(node * 2 + 1, middle + 1, right,
                   query_left, query_right, value);
        pull(node);
    }

    void update_set(int node, int left, int right,
                    int query_left, int query_right, long long value) {
        if (query_right < left || right < query_left) {
            return;
        }
        if (query_left <= left && right <= query_right) {
            apply_set(node, left, right, value);
            return;
        }

        push(node, left, right);
        const int middle = (left + right) / 2;
        update_set(node * 2, left, middle,
                   query_left, query_right, value);
        update_set(node * 2 + 1, middle + 1, right,
                   query_left, query_right, value);
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

    LazySegmentTree tree(values);

    for (int query = 0; query < query_count; ++query) {
        int type, left, right;
        cin >> type >> left >> right;
        --left;
        --right;

        if (type == 3) {
            cout << tree.range_sum(left, right) << '\n';
        } else {
            long long value;
            cin >> value;

            if (type == 1) {
                tree.add_range(left, right, value);
            } else {
                tree.set_range(left, right, value);
            }
        }
    }

    return 0;
}
