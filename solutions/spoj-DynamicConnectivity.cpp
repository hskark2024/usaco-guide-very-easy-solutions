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

struct LinkCutTree {
    struct Node {
        int ch[2] = {0, 0};
        int p = 0;
        bool rev = false;
    };

    vector<Node> t;

    explicit LinkCutTree(int n) : t(n + 1) {}

    bool is_root(int x) {
        int p = t[x].p;
        return p == 0 || (t[p].ch[0] != x && t[p].ch[1] != x);
    }

    void push(int x) {
        if (!x || !t[x].rev) return;
        swap(t[x].ch[0], t[x].ch[1]);
        if (t[x].ch[0]) t[t[x].ch[0]].rev ^= 1;
        if (t[x].ch[1]) t[t[x].ch[1]].rev ^= 1;
        t[x].rev = false;
    }

    void rotate(int x) {
        int p = t[x].p, g = t[p].p;
        int dir = (t[p].ch[1] == x);
        int b = t[x].ch[dir ^ 1];
        if (!is_root(p)) t[g].ch[t[g].ch[1] == p] = x;
        t[x].p = g;
        t[x].ch[dir ^ 1] = p;
        t[p].p = x;
        t[p].ch[dir] = b;
        if (b) t[b].p = p;
    }

    void splay(int x) {
        vector<int> st;
        int y = x;
        st.push_back(y);
        while (!is_root(y)) {
            y = t[y].p;
            st.push_back(y);
        }
        while (!st.empty()) {
            push(st.back());
            st.pop_back();
        }
        while (!is_root(x)) {
            int p = t[x].p, g = t[p].p;
            if (!is_root(p)) {
                bool zigzig = (t[p].ch[0] == x) == (t[g].ch[0] == p);
                rotate(zigzig ? p : x);
            }
            rotate(x);
        }
    }

    void access(int x) {
        int last = 0;
        for (int y = x; y; y = t[y].p) {
            splay(y);
            t[y].ch[1] = last;
            last = y;
        }
        splay(x);
    }

    void makeroot(int x) {
        access(x);
        t[x].rev ^= 1;
    }

    int findroot(int x) {
        access(x);
        while (true) {
            push(x);
            if (!t[x].ch[0]) break;
            x = t[x].ch[0];
        }
        splay(x);
        return x;
    }

    bool connected(int u, int v) {
        return findroot(u) == findroot(v);
    }

    void link(int u, int v) {
        makeroot(u);
        if (findroot(v) != u) t[u].p = v;
    }

    void cut(int u, int v) {
        makeroot(u);
        access(v);
        if (t[v].ch[0] == u && t[u].ch[1] == 0) {
            t[v].ch[0] = 0;
            t[u].p = 0;
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    LinkCutTree lct(n);
    while (m--) {
        string op;
        int a, b;
        cin >> op >> a >> b;
        if (op == "add") lct.link(a, b);
        else if (op == "rem") lct.cut(a, b);
        else cout << (lct.connected(a, b) ? "YES" : "NO") << '\n';
    }
    return 0;
}
