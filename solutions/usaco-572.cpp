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

    if (FILE *f = fopen("bcount.in", "r")) {
        fclose(f);
        freopen("bcount.in", "r", stdin);
        freopen("bcount.out", "w", stdout);
    }

    int n, q;
    cin >> n >> q;
    vector<array<int, 3>> pref(n + 1);
    for (int i = 1; i <= n; i++) {
        int b;
        cin >> b;
        pref[i] = pref[i - 1];
        pref[i][b - 1]++;
    }
    while (q--) {
        int l, r;
        cin >> l >> r;
        for (int b = 0; b < 3; b++) {
            if (b) cout << ' ';
            cout << pref[r][b] - pref[l - 1][b];
        }
        cout << '\n';
    }
    return 0;
}
