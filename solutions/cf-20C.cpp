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

    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> g(n + 1);
    for (int i = 0; i < m; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        g[a].push_back({b, w});
        g[b].push_back({a, w});
    }
    const long long INF = numeric_limits<long long>::max() / 4;
    vector<long long> dist(n + 1, INF);
    vector<int> parent(n + 1, -1);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
    dist[1] = 0;
    pq.push({0, 1});
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d != dist[u]) continue;
        for (auto [v, w] : g[u]) {
            if (dist[v] > d + w) {
                dist[v] = d + w;
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }
    if (dist[n] == INF) {
        cout << -1 << '\n';
        return 0;
    }
    vector<int> path;
    for (int u = n; u != -1; u = parent[u]) path.push_back(u);
    reverse(path.begin(), path.end());
    for (int i = 0; i < (int)path.size(); i++) {
        if (i) cout << ' ';
        cout << path[i];
    }
    cout << '\n';
    return 0;
}
