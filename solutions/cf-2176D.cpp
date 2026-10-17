#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

namespace {
constexpr int MODULUS = 998244353;

struct Edge {
    int from;
    int to;
    long long endpoint_sum;
};

void add_modulo(int &target, int value) {
    target += value;
    if (target >= MODULUS) {
        target -= MODULUS;
    }
}
}  // namespace

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int test_count;
    cin >> test_count;
    while (test_count--) {
        int vertex_count, edge_count;
        cin >> vertex_count >> edge_count;

        vector<long long> value(vertex_count);
        for (long long &number : value) {
            cin >> number;
        }

        vector<Edge> edges(edge_count);
        for (Edge &edge : edges) {
            cin >> edge.from >> edge.to;
            --edge.from;
            --edge.to;

            // The largest possible sum is 2 * 10^18, which still fits in a
            // signed 64-bit integer.
            edge.endpoint_sum = value[edge.from] + value[edge.to];
        }

        // A Fibonacci continuation after u -> v must go to a vertex w whose
        // value is a[u] + a[v]. The next edge v -> w has an even larger
        // endpoint sum, so descending endpoint sums give a valid DP order.
        sort(edges.begin(), edges.end(), [](const Edge &left, const Edge &right) {
            return left.endpoint_sum > right.endpoint_sum;
        });

        // ways[u][x] stores the number of already processed Fibonacci paths
        // that start at u and whose second vertex has value x. Several edges
        // can end at different vertices carrying the same value, so their
        // counts are deliberately combined under one map key.
        vector<map<long long, int>> ways(vertex_count);
        int answer = 0;

        for (const Edge &edge : edges) {
            const int u = edge.from;
            const int v = edge.to;

            // The one-edge path u -> v is always valid. Every longer path is
            // formed by appending a path from v whose next value is exactly
            // a[u] + a[v]. Those states were processed earlier because all
            // vertex values are positive.
            int path_count = 1;
            const auto continuation = ways[v].find(edge.endpoint_sum);
            if (continuation != ways[v].end()) {
                add_modulo(path_count, continuation->second);
            }

            add_modulo(ways[u][value[v]], path_count);
            add_modulo(answer, path_count);
        }

        cout << answer << '\n';
    }

    return 0;
}
