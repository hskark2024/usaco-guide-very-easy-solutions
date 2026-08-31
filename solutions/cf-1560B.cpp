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
        int a, b, c;
        cin >> a >> b >> c;
        int d = abs(a - b);
        int n = 2 * d;
        if (a > n || b > n || c > n || d == 0) {
            cout << -1 << '\n';
        } else {
            int ans = c + d;
            if (ans > n) ans -= n;
            cout << ans << '\n';
        }
    }
    return 0;
}
