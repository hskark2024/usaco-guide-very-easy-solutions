#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    constexpr int MOD = 1'000'000'007;
    const int total = n * (n + 1) / 2;
    if (total % 2 != 0) {
        // Integer sums cannot split an odd total into two equal halves.
        cout << 0 << '\n';
        return 0;
    }
    const int target = total / 2;

    // Every unordered partition has exactly one side NOT containing n.
    // Count that side using only 1..n-1. This chooses one representative
    // per partition and avoids double-counting or modular division by two.
    // ways[s] counts subsets of processed numbers whose exact sum is s.
    vector<int> ways(target + 1, 0);
    ways[0] = 1;  // One empty subset; all positive sums start impossible.
    for (int value = 1; value < n; ++value) {
        // Descending order leaves ways[sum-value] in the previous-number
        // state. Thus this distinct number can be included only once.
        for (int sum = target; sum >= value; --sum) {
            // Skip value (existing ways[sum]) or include it after a subset
            // totaling sum-value. The two classes of subsets are disjoint.
            ways[sum] += ways[sum - value];
            // Both terms are below MOD, so their sum fits in signed int.
            if (ways[sum] >= MOD) ways[sum] -= MOD;
        }
    }
    cout << ways[target] << '\n';
    return 0;
}
