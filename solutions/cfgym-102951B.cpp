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

    int n, x;
    cin >> n >> x;
    vector<int> a(n);
    for (int &v : a) cin >> v;
    sort(a.begin(), a.end());
    int count = 0;
    for (int v : a) {
        if (x >= v) {
            x -= v;
            count++;
        }
    }
    cout << count << '\n';
    return 0;
}
