#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    const int MOD = 1'000'000'007;

    // dp[column] stores the number of ways to reach the cell in the current
    // row and this column. Before we update it, the same entry still stores
    // the answer for the cell directly above. This lets one array represent
    // an entire n by n table without losing either incoming direction.
    vector<int> dp(n, 0);

    for (int row = 0; row < n; ++row) {
        string cells;
        cin >> cells;

        for (int column = 0; column < n; ++column) {
            if (cells[column] == '*') {
                // A trap cannot be entered. Clearing this entry is essential:
                // otherwise its old "from above" count could leak into the
                // next row and pretend that a path passed through the trap.
                dp[column] = 0;
                continue;
            }

            if (row == 0 && column == 0) {
                // There is one empty path that starts on the first square.
                dp[column] = 1;
                continue;
            }

            // dp[column] is the contribution from above. Because columns are
            // processed left to right, dp[column - 1] has already become the
            // current row's contribution from the left.
            const int from_above = dp[column];
            const int from_left = (column == 0 ? 0 : dp[column - 1]);
            dp[column] = from_above + from_left;

            // Each summand is below MOD, so one subtraction is sufficient.
            if (dp[column] >= MOD) dp[column] -= MOD;
        }
    }

    cout << dp[n - 1] << '\n';
    return 0;
}
