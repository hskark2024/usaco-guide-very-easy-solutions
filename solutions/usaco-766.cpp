#include <array>
#include <iostream>
#include <vector>

using namespace std;

constexpr long long MOD = 1'000'000'007LL;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int node_count, fixed_count;
    cin >> node_count >> fixed_count;

    vector<vector<int>> neighbors(node_count);
    for (int edge = 0; edge + 1 < node_count; ++edge) {
        int first, second;
        cin >> first >> second;
        --first;
        --second;
        neighbors[first].push_back(second);
        neighbors[second].push_back(first);
    }

    // fixed_color[v] is -1 for an unpainted barn and 0..2 otherwise.
    vector<int> fixed_color(node_count, -1);
    for (int index = 0; index < fixed_count; ++index) {
        int barn, color;
        cin >> barn >> color;
        fixed_color[barn - 1] = color - 1;
    }

    // Form parent links and an order whose reverse is postorder.  Iteration is
    // important because a 100,000-node path is a legal input.
    vector<int> parent(node_count, -1);
    vector<int> order{0};
    order.reserve(node_count);
    parent[0] = 0;
    for (int index = 0; index < node_count; ++index) {
        const int vertex = order[index];
        for (const int next : neighbors[vertex]) {
            if (next == parent[vertex]) {
                continue;
            }
            parent[next] = vertex;
            order.push_back(next);
        }
    }

    // ways[v][color] counts valid paintings of v's entire subtree when v has
    // this color.  A pre-painted barn starts with only its required color on.
    vector<array<long long, 3>> ways(node_count, {1, 1, 1});
    for (int vertex = 0; vertex < node_count; ++vertex) {
        if (fixed_color[vertex] == -1) {
            continue;
        }
        ways[vertex] = {0, 0, 0};
        ways[vertex][fixed_color[vertex]] = 1;
    }

    for (int index = node_count - 1; index >= 0; --index) {
        const int vertex = order[index];
        for (const int child : neighbors[vertex]) {
            if (parent[child] != vertex) {
                continue;
            }

            // If the parent uses color c, the child may use either of the two
            // other colors.  Different child subtrees combine by multiplication.
            const long long total_child =
                (ways[child][0] + ways[child][1] + ways[child][2]) % MOD;
            for (int color = 0; color < 3; ++color) {
                const long long allowed_child =
                    (total_child - ways[child][color] + MOD) % MOD;
                ways[vertex][color] =
                    ways[vertex][color] * allowed_child % MOD;
            }
        }
    }

    cout << (ways[0][0] + ways[0][1] + ways[0][2]) % MOD << '\n';
    return 0;
}
