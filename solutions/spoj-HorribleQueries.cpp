#include <iostream>
#include <vector>
using namespace std;

// A Fenwick tree supports point additions and prefix sums in O(log n).  The
// problem asks for range additions, so we combine two Fenwick trees below.
class FenwickTree {
public:
    explicit FenwickTree(int size) : tree_(size + 1, 0) {}

    void add(int index, long long value) {
        // The public interface is one-based, exactly like the problem input.
        for (; index < static_cast<int>(tree_.size()); index += index & -index) {
            tree_[index] += value;
        }
    }

    long long prefix_sum(int index) const {
        long long total = 0;
        for (; index > 0; index -= index & -index) {
            total += tree_[index];
        }
        return total;
    }

private:
    vector<long long> tree_;
};

// Suppose a range addition of x begins at position left.  At a prefix ending
// at p, its contribution is x * (p - left + 1), which can be rewritten as
// p*x - x*(left-1).  One Fenwick tree stores the x coefficients and the other
// stores the correction terms.  A subtraction event at right+1 stops both.
class RangeAddRangeSum {
public:
    explicit RangeAddRangeSum(int size)
        // One extra logical position accepts the stopping event at n + 1.
        : coefficient_(size + 1), correction_(size + 1) {}

    void add_range(int left, int right, long long value) {
        add_boundary(left, value);
        add_boundary(right + 1, -value);
    }

    long long range_sum(int left, int right) const {
        return prefix_sum(right) - prefix_sum(left - 1);
    }

private:
    FenwickTree coefficient_;
    FenwickTree correction_;

    void add_boundary(int position, long long value) {
        coefficient_.add(position, value);
        correction_.add(position, value * (position - 1));
    }

    long long prefix_sum(int position) const {
        // All range additions affecting this endpoint contribute a linear
        // amount; the second tree removes the overcount before their starts.
        return coefficient_.prefix_sum(position) * position
               - correction_.prefix_sum(position);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int test_count;
    cin >> test_count;

    while (test_count--) {
        int size, command_count;
        cin >> size >> command_count;

        // Every test starts with an all-zero array, so no build step is needed.
        RangeAddRangeSum values(size);

        for (int command = 0; command < command_count; ++command) {
            int type, left, right;
            cin >> type >> left >> right;

            if (type == 0) {
                long long added_value;
                cin >> added_value;
                values.add_range(left, right, added_value);
            } else {
                cout << values.range_sum(left, right) << '\n';
            }
        }
    }

    return 0;
}
