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

    string text, pat;
    cin >> text >> pat;
    string s = pat + "#" + text;
    vector<int> pi(s.size());
    for (int i = 1; i < (int)s.size(); i++) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j]) j = pi[j - 1];
        if (s[i] == s[j]) j++;
        pi[i] = j;
    }
    int ans = 0;
    for (int x : pi) if (x == (int)pat.size()) ans++;
    cout << ans << '\n';
    return 0;
}
