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
    long long t;
    cin >> n >> t;
    vector<int> a(n);
    for (int &x : a) cin >> x;
    long long sum = 0;
    int ans = 0, l = 0;
    for (int r = 0; r < n; r++) {
        sum += a[r];
        while (sum > t && l <= r) sum -= a[l++];
        ans = max(ans, r - l + 1);
    }
    cout << ans << '\n';
    return 0;
}
