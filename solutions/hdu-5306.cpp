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

struct SegTree {
    struct Node {
        long long sum = 0;
        int mx = 0;
        int second = -1;
        int cnt_mx = 0;
    };

    int n;
    vector<Node> st;

    explicit SegTree(const vector<int> &a) {
        n = (int)a.size() - 1;
        st.resize(4 * n + 4);
        build(1, 1, n, a);
    }

    Node merge(Node l, Node r) {
        Node res;
        res.sum = l.sum + r.sum;
        if (l.mx == r.mx) {
            res.mx = l.mx;
            res.cnt_mx = l.cnt_mx + r.cnt_mx;
            res.second = max(l.second, r.second);
        } else if (l.mx > r.mx) {
            res.mx = l.mx;
            res.cnt_mx = l.cnt_mx;
            res.second = max(l.second, r.mx);
        } else {
            res.mx = r.mx;
            res.cnt_mx = r.cnt_mx;
            res.second = max(l.mx, r.second);
        }
        return res;
    }

    void build(int p, int l, int r, const vector<int> &a) {
        if (l == r) {
            st[p].sum = st[p].mx = a[l];
            st[p].second = -1;
            st[p].cnt_mx = 1;
            return;
        }
        int m = (l + r) / 2;
        build(p * 2, l, m, a);
        build(p * 2 + 1, m + 1, r, a);
        st[p] = merge(st[p * 2], st[p * 2 + 1]);
    }

    void apply_chmin(int p, int x) {
        if (x >= st[p].mx) return;
        st[p].sum -= 1LL * (st[p].mx - x) * st[p].cnt_mx;
        st[p].mx = x;
    }

    void push(int p) {
        apply_chmin(p * 2, st[p].mx);
        apply_chmin(p * 2 + 1, st[p].mx);
    }

    void range_chmin(int p, int l, int r, int ql, int qr, int x) {
        if (qr < l || r < ql || x >= st[p].mx) return;
        if (ql <= l && r <= qr && x > st[p].second) {
            apply_chmin(p, x);
            return;
        }
        push(p);
        int m = (l + r) / 2;
        range_chmin(p * 2, l, m, ql, qr, x);
        range_chmin(p * 2 + 1, m + 1, r, ql, qr, x);
        st[p] = merge(st[p * 2], st[p * 2 + 1]);
    }

    int range_max(int p, int l, int r, int ql, int qr) {
        if (qr < l || r < ql) return 0;
        if (ql <= l && r <= qr) return st[p].mx;
        push(p);
        int m = (l + r) / 2;
        return max(range_max(p * 2, l, m, ql, qr), range_max(p * 2 + 1, m + 1, r, ql, qr));
    }

    long long range_sum(int p, int l, int r, int ql, int qr) {
        if (qr < l || r < ql) return 0;
        if (ql <= l && r <= qr) return st[p].sum;
        push(p);
        int m = (l + r) / 2;
        return range_sum(p * 2, l, m, ql, qr) + range_sum(p * 2 + 1, m + 1, r, ql, qr);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n, m;
        cin >> n >> m;
        vector<int> a(n + 1);
        for (int i = 1; i <= n; i++) cin >> a[i];
        SegTree seg(a);
        while (m--) {
            int op, l, r;
            cin >> op >> l >> r;
            if (op == 0) {
                int x;
                cin >> x;
                seg.range_chmin(1, 1, n, l, r, x);
            } else if (op == 1) {
                cout << seg.range_max(1, 1, n, l, r) << '\n';
            } else {
                cout << seg.range_sum(1, 1, n, l, r) << '\n';
            }
        }
    }
    return 0;
}
