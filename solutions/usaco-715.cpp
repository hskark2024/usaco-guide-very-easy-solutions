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

    if (FILE *f = fopen("maxcross.in", "r")) {
        fclose(f);
        freopen("maxcross.in", "r", stdin);
        freopen("maxcross.out", "w", stdout);
    }

    int n, k, b;
    cin >> n >> k >> b;
    vector<int> broken(n + 1, 0);
    for (int i = 0; i < b; i++) {
        int x;
        cin >> x;
        broken[x] = 1;
    }
    int cur = 0;
    for (int i = 1; i <= k; i++) cur += broken[i];
    int ans = cur;
    for (int r = k + 1; r <= n; r++) {
        cur += broken[r];
        cur -= broken[r - k];
        ans = min(ans, cur);
    }
    cout << ans << '\n';
    return 0;
}
