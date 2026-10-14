#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>
using namespace std;

// Each segment-tree node stores exactly the two facts needed to validate a
// proposed paint interval:
//   1. the largest original value inside it, and
//   2. the smallest required final value inside it.
struct RangeFacts {
    int maximum_original = 0;
    int minimum_target = numeric_limits<int>::max();
};

class SegmentTree {
  public:
    SegmentTree(const vector<int> &original, const vector<int> &target) {
        length_ = static_cast<int>(original.size());
        size_ = 1;
        while (size_ < length_) size_ *= 2;

        tree_.assign(2 * size_, RangeFacts{});
        for (int index = 0; index < length_; ++index) {
            tree_[size_ + index] = {original[index], target[index]};
        }
        for (int node = size_ - 1; node >= 1; --node) {
            tree_[node] = combine(tree_[2 * node], tree_[2 * node + 1]);
        }
    }

    // Return the facts for the inclusive interval [left, right].
    RangeFacts query(int left, int right) const {
        left += size_;
        right += size_;
        RangeFacts left_answer;
        RangeFacts right_answer;

        while (left <= right) {
            if (left % 2 == 1) left_answer = combine(left_answer, tree_[left++]);
            if (right % 2 == 0) right_answer = combine(tree_[right--], right_answer);
            left /= 2;
            right /= 2;
        }
        return combine(left_answer, right_answer);
    }

  private:
    int length_ = 0;
    int size_ = 1;
    vector<RangeFacts> tree_;

    static RangeFacts combine(const RangeFacts &left, const RangeFacts &right) {
        return {
            max(left.maximum_original, right.maximum_original),
            min(left.minimum_target, right.minimum_target),
        };
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int test_count;
    cin >> test_count;
    while (test_count--) {
        int length;
        cin >> length;

        vector<int> original(length), target(length);
        for (int &value : original) cin >> value;
        for (int &value : target) cin >> value;

        // positions[value] lets us find the closest original copy of any
        // target value on either side of an index with two binary searches.
        vector<vector<int>> positions(length + 1);
        for (int index = 0; index < length; ++index) {
            positions[original[index]].push_back(index);
        }

        SegmentTree facts(original, target);
        bool possible = true;

        for (int index = 0; index < length && possible; ++index) {
            // An operation replaces values by an interval maximum, so no
            // element can ever decrease.
            if (original[index] > target[index]) {
                possible = false;
                break;
            }

            const int wanted = target[index];
            const vector<int> &sources = positions[wanted];
            auto first_not_left = lower_bound(sources.begin(), sources.end(), index);

            // A source at source_index can spread `wanted` to `index` exactly
            // when:
            //   * no original value in between is larger than wanted, and
            //   * no final target in between is smaller than wanted.
            // The first condition makes the interval maximum exactly wanted.
            // The second ensures we do not permanently overpaint a position
            // whose final answer must be smaller.
            auto source_works = [&](int source_index) {
                const int left = min(index, source_index);
                const int right = max(index, source_index);
                const RangeFacts interval = facts.query(left, right);
                return interval.maximum_original <= wanted &&
                       interval.minimum_target >= wanted;
            };

            bool supplied = false;

            // If a valid source exists to the right, the nearest source is
            // also valid because its interval is only shorter.
            if (first_not_left != sources.end()) {
                supplied = source_works(*first_not_left);
            }

            // Check the nearest source strictly to the left as well.
            if (!supplied && first_not_left != sources.begin()) {
                supplied = source_works(*prev(first_not_left));
            }

            if (!supplied) possible = false;
        }

        cout << (possible ? "YES" : "NO") << '\n';
    }
}
