#include <bitset>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, target;
    cin >> n >> target;
    constexpr int MAX_TARGET = 500;

    // possible[total][inside] is true when processed coins can form a
    // payment of total, and a marked subset INSIDE that payment sums to
    // inside. Bits compactly represent all inside sums in a single row.
    vector<bitset<MAX_TARGET + 1>> possible(target + 1);
    possible[0].set(0);  // Empty payment, with an empty marked subset.

    for (int i = 0; i < n; ++i) {
        int coin;
        cin >> coin;
        if (coin > target) continue;  // Positive values cannot fit payment.
        // A coin has three choices: outside payment, inside payment but
        // unmarked, or inside both payment and the marked subset.
        // Outside payment keeps each row's existing bits unchanged.
        // Descending payment totals preserve the old source row, so a
        // physical coin is never used twice, even with duplicate values.
        for (int total = target; total >= coin; --total) {
            const auto previous = possible[total - coin];
            // Unmarked: payment grows by coin, inside sum stays unchanged.
            // Marked: both totals grow; shifting bits adds coin to inside.
            possible[total] |= previous | (previous << coin);
        }
    }

    vector<int> answers;
    // Read only payments totaling target. Zero and target are legitimate
    // inside sums (empty marked subset and the entire payment).
    for (int inside = 0; inside <= target; ++inside) {
        if (possible[target].test(inside)) answers.push_back(inside);
    }
    cout << answers.size() << '\n';
    for (size_t i = 0; i < answers.size(); ++i) {
        if (i) cout << ' ';
        cout << answers[i];
    }
    cout << '\n';
    return 0;
}
