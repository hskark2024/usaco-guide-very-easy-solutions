#include <iostream>
#include <vector>

using namespace std;

int main() {
    // The O(n*x) DP is large enough that synchronized iostreams would add
    // avoidable overhead on the biggest test cases.
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int coin_count, target;
    cin >> coin_count >> target;

    // A denomination can be selected repeatedly.  We never need to sort: the
    // input order itself can serve as the one canonical processing order.
    vector<int> coins(coin_count);
    for (int &coin : coins) {
        cin >> coin;
    }

    constexpr int MOD = 1'000'000'007;

    // State meaning:
    // ways[sum] counts combinations using only the coin types processed so
    // far.  The empty combination is the unique way to make sum zero.
    vector<int> ways(target + 1, 0);
    ways[0] = 1;

    // Loop order is crucial.  Processing one denomination at a time gives
    // every multiset a canonical
    // construction order.  Thus 2+3 and 3+2 are the same combination here.
    for (int coin : coins) {
        // Iterate upward so a state updated with this coin can use the same
        // denomination again.  Coins are reusable without a quantity limit.
        for (int sum = coin; sum <= target; ++sum) {
            // Either do not use this denomination (the old ways[sum]) or add
            // one copy to a combination totaling sum - coin.  Because later
            // coin types have not been processed yet, no ordering is counted
            // more than once.
            ways[sum] += ways[sum - coin];
            // Each addend is below MOD, so a single subtraction normalizes it.
            if (ways[sum] >= MOD) {
                ways[sum] -= MOD;
            }
        }
    }

    cout << ways[target] << '\n';
    return 0;
}
