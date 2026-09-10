#include <algorithm>
#include <array>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int test_cases;
    cin >> test_cases;

    while (test_cases--) {
        int boss_count;
        cin >> boss_count;

        vector<int> is_hard(boss_count);
        for (int &boss : is_hard) {
            cin >> boss;
        }

        // dp[defeated][turn] is the minimum number of skip points used after
        // exactly 'defeated' bosses are gone.  turn == 0 means the friend's
        // session comes next; turn == 1 means our session comes next.
        //
        // Keeping the next turn in the state is what enforces alternation.
        // Each transition below defeats either one or two consecutive bosses.
        const int INF = boss_count + 1;
        vector<array<int, 2>> dp(boss_count + 1, {INF, INF});

        // The friend always takes the first session, before any boss is gone.
        dp[0][0] = 0;

        for (int defeated = 0; defeated < boss_count; ++defeated) {
            for (int turn = 0; turn < 2; ++turn) {
                if (dp[defeated][turn] == INF) {
                    continue;  // This state cannot be reached by valid sessions.
                }

                // A session must defeat at least one and at most two bosses.
                for (int take = 1; take <= 2 && defeated + take <= boss_count;
                     ++take) {
                    int extra_skips = 0;

                    if (turn == 0) {
                        // Only the friend needs skip points, and exactly one is
                        // charged for every hard boss in this session.
                        for (int offset = 0; offset < take; ++offset) {
                            extra_skips += is_hard[defeated + offset];
                        }
                    }

                    // Once this session ends, the other player must go next.
                    int &next = dp[defeated + take][turn ^ 1];
                    next = min(next, dp[defeated][turn] + extra_skips);
                }
            }
        }

        // The tower may end after either person's session, so either next-turn
        // state can contain the optimum after every boss has been defeated.
        cout << min(dp[boss_count][0], dp[boss_count][1]) << '\n';
    }

    return 0;
}
