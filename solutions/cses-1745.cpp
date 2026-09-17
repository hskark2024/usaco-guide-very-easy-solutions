#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int coin_count;
    cin >> coin_count;
    vector<int> coins(coin_count);
    int maximum_sum = 0;
    for (int &coin : coins) {
        cin >> coin;
        maximum_sum += coin;  // Every obtainable sum is in [0, total].
    }

    // reachable[s] records whether SOME subset of processed physical coins
    // totals s.  Sum zero is always possible using no coins.  Each coin is
    // used at most once, even when two physical coins share the same value.
    vector<char> reachable(maximum_sum + 1, false);
    reachable[0] = true;

    for (int coin : coins) {
        // Descending order reads only states from before THIS coin.  An
        // ascending loop would wrongly reuse one physical coin many times.
        for (int sum = maximum_sum; sum >= coin; --sum) {
            if (reachable[sum - coin]) reachable[sum] = true;
        }
    }

    vector<int> answers;
    for (int sum = 1; sum <= maximum_sum; ++sum) {
        if (reachable[sum]) answers.push_back(sum);
    }
    cout << answers.size() << '\n';
    for (size_t i = 0; i < answers.size(); ++i) {
        if (i) cout << ' ';
        cout << answers[i];
    }
    cout << '\n';
    return 0;
}
