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

int wins(const array<int, 3> &cnt) {
    int playH = cnt[2];
    int playP = cnt[0];
    int playS = cnt[1];
    return max(playH, max(playP, playS));
}

int idx(char c) {
    if (c == 'H') return 0;
    if (c == 'P') return 1;
    return 2;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (FILE *f = fopen("hps.in", "r")) {
        fclose(f);
        freopen("hps.in", "r", stdin);
        freopen("hps.out", "w", stdout);
    }

    int n;
    cin >> n;
    vector<array<int, 3>> pref(n + 1);
    for (int i = 0; i < n; i++) {
        char c;
        cin >> c;
        pref[i + 1] = pref[i];
        pref[i + 1][idx(c)]++;
    }
    int ans = 0;
    for (int split = 0; split <= n; split++) {
        array<int, 3> left = pref[split];
        array<int, 3> right;
        for (int j = 0; j < 3; j++) right[j] = pref[n][j] - pref[split][j];
        ans = max(ans, wins(left) + wins(right));
    }
    cout << ans << '\n';
    return 0;
}
