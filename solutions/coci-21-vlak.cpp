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
    array<int, 26> next;
    bool ok[2] = {false, false};
    bool win[2] = {false, false};
    Node() { next.fill(-1); }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<Node> trie(1);
    auto insert_word = [&](const string &s, int player) {
        int u = 0;
        for (char c : s) {
            int id = c - 'a';
            if (trie[u].next[id] == -1) {
                trie[u].next[id] = (int)trie.size();
                trie.push_back(Node());
            }
            u = trie[u].next[id];
            trie[u].ok[player] = true;
        }
    };

    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        insert_word(s, 0);
    }
    int m;
    cin >> m;
    for (int i = 0; i < m; i++) {
        string s;
        cin >> s;
        insert_word(s, 1);
    }

    function<void(int)> dfs = [&](int u) {
        for (int v : trie[u].next) if (v != -1) dfs(v);
        for (int player = 0; player < 2; player++) {
            trie[u].win[player] = false;
            for (int v : trie[u].next) {
                if (v != -1 && trie[v].ok[player] && !trie[v].win[player ^ 1]) {
                    trie[u].win[player] = true;
                }
            }
        }
    };
    dfs(0);
    cout << (trie[0].win[0] ? "Nina" : "Emilija") << '\n';
    return 0;
}
