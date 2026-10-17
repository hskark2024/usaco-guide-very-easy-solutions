#include <algorithm>
#include <array>
#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;

namespace {
constexpr int BOUND = 3;
constexpr int STATE_COUNT = 2 * BOUND + 1;
constexpr int INFINITY_COST = 1'000'000'000;

bool matches_sign(int prefix_sum, char sign) {
    if (sign == '0') {
        return prefix_sum == 0;
    }
    if (sign == '+') {
        return prefix_sum > 0;
    }
    return prefix_sum < 0;
}
}  // namespace

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int test_count;
    cin >> test_count;
    while (test_count--) {
        int length;
        string signs;
        cin >> length >> signs;

        // State values represent the previous prefix sum in [-3, 3]. This
        // finite range is sufficient: any feasible sign string has a witness
        // with cost at most 3, obtained by alternating small values of the
        // required sign. A solution with cost 1 or 2 can also be normalized
        // into this range without changing any sign or using a zero step.
        array<int, STATE_COUNT> previous;
        previous.fill(INFINITY_COST);
        previous[BOUND] = 0;  // Before a[1], the empty prefix sum is zero.

        for (char sign : signs) {
            array<int, STATE_COUNT> current;
            current.fill(INFINITY_COST);

            for (int old_index = 0; old_index < STATE_COUNT; ++old_index) {
                if (previous[old_index] == INFINITY_COST) {
                    continue;
                }
                const int old_sum = old_index - BOUND;

                for (int new_sum = -BOUND; new_sum <= BOUND; ++new_sum) {
                    if (!matches_sign(new_sum, sign) || new_sum == old_sum) {
                        continue;
                    }

                    // a[i] is the difference of adjacent prefix sums. Equal
                    // states would make a[i] zero, which is forbidden.
                    const int new_cost =
                        max(previous[old_index], abs(new_sum - old_sum));
                    int &best = current[new_sum + BOUND];
                    best = min(best, new_cost);
                }
            }

            previous = current;
        }

        const int answer = *min_element(previous.begin(), previous.end());
        cout << (answer == INFINITY_COST ? -1 : answer) << '\n';
    }

    return 0;
}
