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
        vector<int> a(3);
        for (int &x : a) cin >> x;
        for (int i = 0; i < 3; i++) {
            int best_other = 0;
            for (int j = 0; j < 3; j++) if (i != j) best_other = max(best_other, a[j]);
            int need = max(0, best_other + 1 - a[i]);
            if (i) cout << ' ';
            cout << need;
        }
        cout << '\n';
    }
    return 0;
}
