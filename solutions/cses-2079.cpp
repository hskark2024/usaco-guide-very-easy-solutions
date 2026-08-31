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
    vector<vector<int>> g(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    vector<int> sz(n + 1);
    function<void(int, int)> dfs = [&](int u, int p) {
        sz[u] = 1;
        for (int v : g[u]) if (v != p) {
            dfs(v, u);
            sz[u] += sz[v];
        }
    };
    dfs(1, 0);
    int u = 1, p = 0;
    bool moved = true;
    while (moved) {
        moved = false;
        for (int v : g[u]) if (v != p && sz[v] > n / 2) {
            p = u;
            u = v;
            moved = true;
            break;
        }
    }
    cout << u << '\n';
    return 0;
}
