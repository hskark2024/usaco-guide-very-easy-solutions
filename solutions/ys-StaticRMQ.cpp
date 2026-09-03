#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    vector<int> values(n);
    for (int &value : values) cin >> value;

    vector<int> floor_log(n + 1, 0);
    for (int length = 2; length <= n; ++length) {
        floor_log[length] = floor_log[length / 2] + 1;
    }

    int levels = floor_log[n] + 1;
    vector<vector<int>> minimum(levels, vector<int>(n));
    minimum[0] = values;
    for (int level = 1; level < levels; ++level) {
        int half = 1 << (level - 1);
        int length = 1 << level;
        for (int left = 0; left + length <= n; ++left) {
            minimum[level][left] =
                min(minimum[level - 1][left],
                    minimum[level - 1][left + half]);
        }
    }

    while (q--) {
        int left, right;
        cin >> left >> right;
        int level = floor_log[right - left];
        int length = 1 << level;
        cout << min(minimum[level][left], minimum[level][right - length])
             << '\n';
    }
}
