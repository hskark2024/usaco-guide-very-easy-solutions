#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int value_count;
    cin >> value_count;

    // smallest_tail[length - 1] stores the smallest possible final value of
    // any strictly increasing subsequence of this length seen so far.  A
    // smaller tail is always at least as useful for extending later.
    vector<int> smallest_tail;
    smallest_tail.reserve(value_count);

    for (int index = 0; index < value_count; ++index) {
        int value;
        cin >> value;

        // lower_bound finds the first tail >= value.  Replacing that tail
        // preserves its subsequence length while improving (or matching) its
        // ending value.  Using >= instead of > is essential: equal values do
        // not extend a strictly increasing subsequence.
        auto position = lower_bound(
            smallest_tail.begin(),
            smallest_tail.end(),
            value
        );

        if (position == smallest_tail.end()) {
            // Every existing tail is smaller, so value extends the longest
            // known subsequence by one element.
            smallest_tail.push_back(value);
        } else {
            // This value gives the same-length subsequence a no-larger tail.
            *position = value;
        }
    }

    // There is one representative tail for every achievable length.
    cout << smallest_tail.size() << '\n';
    return 0;
}
