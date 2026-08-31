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
    long long sum = 0, mx = 0;
    for (int i = 0; i < n; i++) {
        long long x;
        cin >> x;
        sum += x;
        mx = max(mx, x);
    }
    cout << max(sum, 2 * mx) << '\n';
    return 0;
}
