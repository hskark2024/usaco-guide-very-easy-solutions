#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

// Codeforces 321C: Ciel the Commander
//
// A centroid splits its current component into pieces of at most half the
// size.  Label that centroid with the current rank, remove it, and repeat on
// every remaining piece.  The centroid-decomposition level becomes A, B, ...
// and directly satisfies the required ranked-path property.
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int node_count;
    cin >> node_count;

    vector<vector<int>> graph(node_count + 1);
    for (int edge = 1; edge < node_count; ++edge) {
        int first, second;
        cin >> first >> second;
        graph[first].push_back(second);
        graph[second].push_back(first);
    }

    vector<bool> removed(node_count + 1, false);
    vector<int> answer_level(node_count + 1, -1);
    vector<int> parent(node_count + 1), subtree_size(node_count + 1);

    // A pending job identifies one still-connected component by any vertex in
    // it, plus the letter level that its centroid must receive.
    vector<pair<int, int>> pending = {{1, 0}};
    bool possible = true;

    while (!pending.empty()) {
        const auto [entry, level] = pending.back();
        pending.pop_back();

        // The alphabet provides 26 ranks.  Under the official N <= 100000
        // limit, balanced centroid splits actually need fewer than 26, but
        // keeping this guard makes the output contract explicit.
        if (level >= 26) {
            possible = false;
            break;
        }

        // Collect exactly this component while treating previously chosen
        // centroids as deleted.  The same order also gives us a rooted tree.
        vector<int> component = {entry};
        parent[entry] = 0;
        for (size_t index = 0; index < component.size(); ++index) {
            const int vertex = component[index];
            for (const int next : graph[vertex]) {
                if (removed[next] || next == parent[vertex]) continue;
                parent[next] = vertex;
                component.push_back(next);
            }
        }

        // Reverse traversal computes rooted subtree sizes without recursive
        // calls, so a long chain cannot overflow the program stack.
        for (auto iterator = component.rbegin(); iterator != component.rend();
             ++iterator) {
            const int vertex = *iterator;
            subtree_size[vertex] = 1;
            for (const int next : graph[vertex]) {
                if (!removed[next] && parent[next] == vertex) {
                    subtree_size[vertex] += subtree_size[next];
                }
            }
        }

        const int component_size = static_cast<int>(component.size());
        int centroid = -1;

        // Removing vertex v leaves one piece for each rooted child and one
        // piece above v.  A centroid is exactly a vertex whose largest such
        // piece has at most half the component's vertices.
        for (const int vertex : component) {
            int largest_piece = component_size - subtree_size[vertex];
            for (const int next : graph[vertex]) {
                if (!removed[next] && parent[next] == vertex) {
                    largest_piece = max(largest_piece, subtree_size[next]);
                }
            }
            if (2 * largest_piece <= component_size) {
                centroid = vertex;
                break;
            }
        }

        answer_level[centroid] = level;
        removed[centroid] = true;

        // After deleting the centroid, every nonremoved neighbor belongs to a
        // different component.  Their centroids receive the next letter.
        for (const int next : graph[centroid]) {
            if (!removed[next]) pending.push_back({next, level + 1});
        }
    }

    if (!possible) {
        cout << "Impossible!\n";
        return 0;
    }

    for (int vertex = 1; vertex <= node_count; ++vertex) {
        if (vertex > 1) cout << ' ';
        cout << static_cast<char>('A' + answer_level[vertex]);
    }
    cout << '\n';
    return 0;
}
