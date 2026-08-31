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

    int n, x;
    cin >> n >> x;
    vector<int> coins(n);
    for (int &c : coins) cin >> c;
    const int INF = 1e9;
    vector<int> dp(x + 1, INF);
    dp[0] = 0;
    for (int s = 1; s <= x; s++) {
        for (int c : coins) if (s >= c) {
            dp[s] = min(dp[s], dp[s - c] + 1);
        }
    }
    cout << (dp[x] == INF ? -1 : dp[x]) << '\n';
    return 0;
}
