#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int query_count, target;
    cin >> query_count >> target;
    constexpr int MOD = 998'244'353;

    // ways[s] counts subsets of the distinguishable balls currently present
    // whose values sum to s.  The empty subset always supplies ways[0] = 1.
    // Values above target have no effect on states through target, so the
    // same array handles every legal query without rebuilding from scratch.
    vector<int> ways(target + 1, 0);
    ways[0] = 1;

    while (query_count--) {
        char operation;
        int value;
        cin >> operation >> value;

        if (value <= target && operation == '+') {
            // Adding this single distinct ball changes the generating
            // function F(z) to F(z) * (1 + z^value).  A downward scan uses
            // each OLD ways[s-value], before it has included this new ball.
            // An upward scan would accidentally pick the same ball twice.
            for (int sum = target; sum >= value; --sum) {
                ways[sum] += ways[sum - value];
                if (ways[sum] >= MOD) ways[sum] -= MOD;
            }
        } else if (value <= target && operation == '-') {
            // Let old[s] be the state with the ball and new[s] without it.
            // old[s] = new[s] + new[s-value], so recover new[s] by
            // subtraction.  Scan UPWARD: new[s-value] must already have
            // been recovered, including when multiple equal balls remain.
            for (int sum = value; sum <= target; ++sum) {
                ways[sum] -= ways[sum - value];
                if (ways[sum] < 0) ways[sum] += MOD;
            }
        }

        // The judge requests one answer after every operation, even if the
        // changed ball's value exceeds K and leaves this truncated DP alone.
        cout << ways[target] << '\n';
    }
    return 0;
}
