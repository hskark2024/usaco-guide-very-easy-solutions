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
    vector<int> p(n + 1);
    for (int i = 1; i <= n; i++) cin >> p[i];
    for (int start = 1; start <= n; start++) {
        vector<int> seen(n + 1, 0);
        int u = start;
        while (!seen[u]) {
            seen[u] = 1;
            u = p[u];
        }
        if (start > 1) cout << ' ';
        cout << u;
    }
    cout << '\n';
    return 0;
}
