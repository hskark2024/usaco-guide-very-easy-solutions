#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

using int64 = long long;

// Return every subset sum of values[begin..end).  A half contains at most
// twenty numbers, so its list has at most 2^20 entries and fits comfortably.
static vector<int64> make_subset_sums(const vector<int64> &values,
                                      int begin, int end) {
    vector<int64> sums = {0};  // The empty subset is important too.

    for (int index = begin; index < end; ++index) {
        const int old_size = static_cast<int>(sums.size());

        // Every old subset gives one new subset after values[index] is added.
        // Only read the old prefix: newly appended sums must not be reused in
        // the same iteration.
        for (int mask = 0; mask < old_size; ++mask) {
            sums.push_back(sums[mask] + values[index]);
        }
    }
    return sums;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int length;
    int64 target;
    cin >> length >> target;

    vector<int64> values(length);
    for (int64 &value : values) cin >> value;

    // Enumerating all 2^40 subsets is too expensive.  Splitting the array
    // turns that into two lists of at most 2^20 subset sums.
    const int middle = length / 2;
    vector<int64> left_sums = make_subset_sums(values, 0, middle);
    vector<int64> right_sums = make_subset_sums(values, middle, length);
    sort(right_sums.begin(), right_sums.end());

    int64 answer = 0;
    for (int64 left_sum : left_sums) {
        const int64 needed = target - left_sum;

        // equal_range counts multiplicity.  If several different right-half
        // subsets have the same sum, every one is a different valid choice.
        auto range = equal_range(right_sums.begin(), right_sums.end(), needed);
        answer += range.second - range.first;
    }

    // Up to 2^40 subsets may work, which is larger than a 32-bit integer.
    cout << answer << '\n';
    return 0;
}
