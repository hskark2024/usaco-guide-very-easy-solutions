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

    if (FILE *f = fopen("teleport.in", "r")) {
        fclose(f);
        freopen("teleport.in", "r", stdin);
        freopen("teleport.out", "w", stdout);
    }

    long long a, b, x, y;
    cin >> a >> b >> x >> y;
    long long ans = llabs(a - b);
    ans = min(ans, llabs(a - x) + llabs(b - y));
    ans = min(ans, llabs(a - y) + llabs(b - x));
    cout << ans << '\n';
    return 0;
}
