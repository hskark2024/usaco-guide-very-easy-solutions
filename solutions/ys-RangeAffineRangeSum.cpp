#include <iostream>
#include <vector>
using namespace std;

// Every value and answer belongs to this finite field.
constexpr long long MOD = 998244353;

// A lazy tag represents the function f(x) = multiply * x + add.
// Each node stores the sum of its interval after all tags that cover the node.
class LazyAffineTree {
public:
    explicit LazyAffineTree(const vector<long long> &values)
        : size_(static_cast<int>(values.size())),
          sum_(4 * size_, 0),
          lazy_multiply_(4 * size_, 1),
          lazy_add_(4 * size_, 0) {
        build(1, 0, size_, values);
    }

    void transform(int query_left, int query_right,
                   long long multiply, long long add) {
        transform(1, 0, size_, query_left, query_right, multiply, add);
    }

    long long range_sum(int query_left, int query_right) {
        return range_sum(1, 0, size_, query_left, query_right);
    }

private:
    int size_;
    vector<long long> sum_;
    vector<long long> lazy_multiply_;
    vector<long long> lazy_add_;

    void build(int node, int left, int right,
               const vector<long long> &values) {
        // All tree intervals are half-open: [left, right).
        if (right - left == 1) {
            sum_[node] = values[left] % MOD;
            return;
        }

        const int middle = (left + right) / 2;
        build(node * 2, left, middle, values);
        build(node * 2 + 1, middle, right, values);
        pull(node);
    }

    void pull(int node) {
        sum_[node] = (sum_[node * 2] + sum_[node * 2 + 1]) % MOD;
    }

    void apply(int node, int left, int right,
               long long multiply, long long add) {
        const long long length = right - left;

        // Applying f(x)=b*x+c to every value changes an interval sum S into
        // b*S + c*length.  Modulo arithmetic keeps all products in range.
        sum_[node] = (multiply * sum_[node] + add * length) % MOD;

        // The node may already be waiting to apply g(x)=m*x+a below it.
        // The newly arrived operation happens later, so children need f(g(x)):
        //     f(g(x)) = b*(m*x+a)+c = (b*m)x + (b*a+c).
        // Notice that reversing this order would be incorrect because affine
        // function composition is not commutative.
        lazy_multiply_[node] = multiply * lazy_multiply_[node] % MOD;
        lazy_add_[node] = (multiply * lazy_add_[node] + add) % MOD;
    }

    void push(int node, int left, int right) {
        if (right - left == 1) {
            return;
        }
        if (lazy_multiply_[node] == 1 && lazy_add_[node] == 0) {
            return;  // The identity function has no work to send downward.
        }

        const int middle = (left + right) / 2;
        apply(node * 2, left, middle,
              lazy_multiply_[node], lazy_add_[node]);
        apply(node * 2 + 1, middle, right,
              lazy_multiply_[node], lazy_add_[node]);

        // After both children inherit the transformation, this node's tag is
        // reset to the identity function f(x)=x.
        lazy_multiply_[node] = 1;
        lazy_add_[node] = 0;
    }

    void transform(int node, int left, int right,
                   int query_left, int query_right,
                   long long multiply, long long add) {
        if (query_right <= left || right <= query_left) {
            return;  // The two half-open intervals do not overlap.
        }
        if (query_left <= left && right <= query_right) {
            apply(node, left, right, multiply, add);
            return;
        }

        // A partial overlap needs accurate child state before recursion.
        push(node, left, right);
        const int middle = (left + right) / 2;
        transform(node * 2, left, middle,
                  query_left, query_right, multiply, add);
        transform(node * 2 + 1, middle, right,
                  query_left, query_right, multiply, add);
        pull(node);
    }

    long long range_sum(int node, int left, int right,
                        int query_left, int query_right) {
        if (query_right <= left || right <= query_left) {
            return 0;  // Zero is the identity for sum.
        }
        if (query_left <= left && right <= query_right) {
            return sum_[node];
        }

        push(node, left, right);
        const int middle = (left + right) / 2;
        return (range_sum(node * 2, left, middle,
                          query_left, query_right)
                + range_sum(node * 2 + 1, middle, right,
                            query_left, query_right)) % MOD;
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

    LazyAffineTree tree(values);
    while (query_count--) {
        int type, left, right;
        cin >> type >> left >> right;

        if (type == 0) {
            long long multiply, add;
            cin >> multiply >> add;
            tree.transform(left, right, multiply, add);
        } else {
            cout << tree.range_sum(left, right) << '\n';
        }
    }

    return 0;
}
