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

struct Node {
    array<int, 26> nxt;
    int parent = -1;
    char ch = 0;
    bool terminal = false;
    Node() { nxt.fill(-1); }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<Node> trie(1);
    int deepest = 0;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        int u = 0;
        for (char c : s) {
            int id = c - 'a';
            if (trie[u].nxt[id] == -1) {
                trie[u].nxt[id] = (int)trie.size();
                trie.push_back(Node());
                trie.back().parent = u;
                trie.back().ch = c;
            }
            u = trie[u].nxt[id];
        }
        trie[u].terminal = true;
        int dep = 0; for (int x = u; x; x = trie[x].parent) dep++;
        int best_dep = 0; for (int x = deepest; x; x = trie[x].parent) best_dep++;
        if (dep > best_dep) deepest = u;
    }

    vector<int> keep(trie.size(), 0);
    for (int u = deepest; u != 0; u = trie[u].parent) keep[u] = 1;

    vector<char> ops;
    function<void(int)> dfs = [&](int u) {
        if (trie[u].terminal) ops.push_back('P');
        int special = -1;
        for (int c = 0; c < 26; c++) {
            int v = trie[u].nxt[c];
            if (v == -1) continue;
            if (keep[v]) special = v;
            else {
                ops.push_back(trie[v].ch);
                dfs(v);
                ops.push_back('-');
            }
        }
        if (special != -1) {
            ops.push_back(trie[special].ch);
            dfs(special);
        }
    };

    dfs(0);
    cout << ops.size() << '\n';
    for (char op : ops) cout << op << '\n';
    return 0;
}
