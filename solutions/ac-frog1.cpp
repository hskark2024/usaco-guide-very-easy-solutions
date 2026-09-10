#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int stone_count;
    cin >> stone_count;

    vector<int> height(stone_count);
    for (int &value : height) {
        cin >> value;
    }

    // dp[i] is the smallest total cost of any valid route that finishes on
    // stone i.  This meaning is useful because the final answer is simply the
    // value stored for the last stone.
    const long long INF = numeric_limits<long long>::max() / 4;
    vector<long long> dp(stone_count, INF);

    // The frog starts on stone 0, so reaching it requires no jump and no cost.
    dp[0] = 0;

    for (int stone = 1; stone < stone_count; ++stone) {
        // One possible final jump comes from the immediately previous stone.
        // Since dp[stone - 1] is already optimal, adding this jump gives the
        // best route whose last jump has length one.
        const long long from_previous =
            dp[stone - 1] + abs(height[stone] - height[stone - 1]);
        dp[stone] = min(dp[stone], from_previous);

        // A length-two jump exists only from stone 2 onward.  Its landing cost
        // depends only on the two endpoint heights, so it can be compared with
        // the length-one choice independently of all earlier decisions.
        if (stone >= 2) {
            const long long from_two_back =
                dp[stone - 2] + abs(height[stone] - height[stone - 2]);
            dp[stone] = min(dp[stone], from_two_back);
        }
    }

    cout << dp.back() << '\n';
    return 0;
}
