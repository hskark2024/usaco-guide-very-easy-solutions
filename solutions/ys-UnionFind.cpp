#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

class DisjointSetUnion {
public:
    explicit DisjointSetUnion(int n) : parent(n), size(n, 1) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if (parent[x] == x) return x;
        return parent[x] = find(parent[x]);
    }

    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return;
        if (size[a] < size[b]) swap(a, b);
        parent[b] = a;
        size[a] += size[b];
    }

    bool connected(int a, int b) { return find(a) == find(b); }

private:
    vector<int> parent;
    vector<int> size;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    DisjointSetUnion dsu(n);

    while (q--) {
        int type, u, v;
        cin >> type >> u >> v;
        if (type == 0) {
            dsu.unite(u, v);
        } else {
            cout << dsu.connected(u, v) << '\n';
        }
    }
    return 0;
}
