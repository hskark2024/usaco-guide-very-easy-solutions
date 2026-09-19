#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, maximum_value;
    cin >> n >> maximum_value;

    vector<int> description(n);
    for (int &value : description) cin >> value;

    const int MOD = 1'000'000'007;

    // previous[value] is the number of valid prefixes ending in value at the
    // preceding position. Two extra sentinel entries stay zero, which makes
    // the transitions for values 1 and maximum_value use the same formula.
    vector<int> previous(maximum_value + 2, 0);
    vector<int> current(maximum_value + 2, 0);

    // Initialize every legal first value that matches the description.
    for (int value = 1; value <= maximum_value; ++value) {
        if (description[0] == 0 || description[0] == value) {
            previous[value] = 1;
        }
    }

    for (int index = 1; index < n; ++index) {
        // Values that do not match this position must remain zero. Clearing
        // the reused row prevents counts from an older position from leaking.
        fill(current.begin(), current.end(), 0);

        for (int value = 1; value <= maximum_value; ++value) {
            if (description[index] != 0 && description[index] != value) {
                continue;
            }

            // Adjacent entries may differ by at most one, so the predecessor
            // is value-1, value, or value+1—no other prefix can be extended.
            long long ways = previous[value - 1];
            ways += previous[value];
            ways += previous[value + 1];
            current[value] = static_cast<int>(ways % MOD);
        }

        previous.swap(current);
    }

    // The final array may end at any value allowed by the last description.
    int answer = 0;
    for (int value = 1; value <= maximum_value; ++value) {
        answer += previous[value];
        if (answer >= MOD) answer -= MOD;
    }

    cout << answer << '\n';
    return 0;
}
