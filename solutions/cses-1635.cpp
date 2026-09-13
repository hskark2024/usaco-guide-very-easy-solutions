#include <iostream>
#include <vector>

using namespace std;

int main() {
    // Fast I/O matters here because the dynamic program may perform close to
    // 100 million transitions at the largest constraints.
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int coin_count, target;
    cin >> coin_count >> target;

    // Every denomination may be used any number of times.  The denominations
    // themselves are distinct, as guaranteed by the original problem.
    vector<int> coins(coin_count);
    for (int &coin : coins) {
        cin >> coin;
    }

    constexpr int MOD = 1'000'000'007;

    // State meaning:
    // ways[sum] counts ordered sequences of coins whose values total sum.
    // There is one way to build zero: choose the empty sequence.  This base
    // state lets a single coin c create the first sequence of total c.
    vector<int> ways(target + 1, 0);
    ways[0] = 1;

    // Transition order is the entire difference between Coin Combinations I
    // and II.  The sum is the outer loop because we are choosing the LAST coin of an
    // ordered sequence.  For example, 2+3 and 3+2 arrive from different
    // preceding sums and are intentionally counted as different answers.
    for (int sum = 1; sum <= target; ++sum) {
        for (int coin : coins) {
            if (coin > sum) {
                continue;
            }

            // Append this coin to every sequence totaling sum - coin.  Those
            // shorter sequences have already been completely counted because
            // coin values are positive and sum - coin is smaller than sum.
            ways[sum] += ways[sum - coin];
            // Both addends are already below MOD, so one subtraction is enough
            // to return the new value to [0, MOD).
            if (ways[sum] >= MOD) {
                ways[sum] -= MOD;
            }
        }
    }

    cout << ways[target] << '\n';
    return 0;
}
