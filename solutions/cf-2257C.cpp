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

    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<vector<int>> child(n + 1);
        for (int v = 2; v <= n; v++) {
            int p;
            cin >> p;
            child[p].push_back(v);
        }
        int m;
        cin >> m;
        vector<int> marked(n + 1, 0);
        for (int i = 0; i < m; i++) {
            int a;
            cin >> a;
            marked[a] = 1;
        }
        vector<int> sub(n + 1, 0), ans;
        function<void(int)> calc = [&](int u) {
            sub[u] = marked[u];
            for (int v : child[u]) {
                calc(v);
                sub[u] += sub[v];
            }
        };
        calc(1);
        function<void(int)> choose = [&](int u) {
            vector<int> useful;
            for (int v : child[u]) if (sub[v] > 0) useful.push_back(v);
            int start = marked[u] ? 0 : min(1, (int)useful.size());
            for (int i = start; i < (int)useful.size(); i++) ans.push_back(useful[i]);
            for (int v : child[u]) choose(v);
        };
        choose(1);
        cout << ans.size();
        for (int v : ans) cout << ' ' << v;
        cout << '\n';
    }
    return 0;
}
