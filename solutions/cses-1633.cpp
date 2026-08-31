#include <algorithm>
#include <array>
#include <cstdio>
#include <deque>
#include <functional>
#include <iostream>
#include <limits>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    const int MOD = 1000000007;
    vector<int> dp(n + 1);
    dp[0] = 1;
    for (int s = 1; s <= n; s++) {
        long long ways = 0;
        for (int d = 1; d <= 6 && d <= s; d++) ways += dp[s - d];
        dp[s] = ways % MOD;
    }
    cout << dp[n] << '\n';
    return 0;
}
