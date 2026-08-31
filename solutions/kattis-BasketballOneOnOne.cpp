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

    string s;
    cin >> s;
    int a = 0, b = 0;
    for (int i = 0; i + 1 < (int)s.size(); i += 2) {
        if (s[i] == 'A') a += s[i + 1] - '0';
        else b += s[i + 1] - '0';
    }
    cout << (a > b ? 'A' : 'B') << '\n';
    return 0;
}
