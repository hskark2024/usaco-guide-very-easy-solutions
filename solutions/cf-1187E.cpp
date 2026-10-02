#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int node_count;
    cin >> node_count;

    vector<vector<int>> neighbors(node_count);
    for (int edge = 0; edge + 1 < node_count; ++edge) {
        int first, second;
        cin >> first >> second;
        --first;
        --second;
        neighbors[first].push_back(second);
        neighbors[second].push_back(first);
    }

    // Pick vertex 0 as a temporary root.  Every legal painting order that
    // starts at a root must paint a vertex's parent before that vertex.  At
    // that moment, the entire rooted subtree of the new vertex is still white,
    // so that move earns exactly the subtree's size.
    vector<int> parent(node_count, -1);
    vector<int> order;
    order.reserve(node_count);
    parent[0] = 0;
    order.push_back(0);

    // Iterative traversal is safe even when the input tree is one very deep
    // path, where a recursive DFS could exhaust the process stack.
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

    // First pass: calculate every subtree size for temporary root 0.
    vector<int> subtree_size(node_count, 1);
    for (int index = node_count - 1; index > 0; --index) {
        const int vertex = order[index];
        subtree_size[parent[vertex]] += subtree_size[vertex];
    }

    // For a fixed starting root, the total score is the sum of all subtree
    // sizes: each vertex contributes its still-white component size when it
    // is painted.  long long is required because the maximum is about N^2/2.
    vector<long long> score(node_count, 0);
    for (const int size : subtree_size) {
        score[0] += size;
    }

    long long answer = score[0];

    // Second pass: reroot across each parent-child edge.  If child has s
    // vertices in its old subtree, those s subtree contributions each lose
    // one level, while the other N-s vertices each gain one level.  Therefore
    // new_score = old_score - s + (N-s) = old_score + N - 2s.
    for (const int vertex : order) {
        for (const int child : neighbors[vertex]) {
            if (parent[child] != vertex) {
                continue;
            }
            score[child] = score[vertex]
                         + node_count
                         - 2LL * subtree_size[child];
            answer = max(answer, score[child]);
        }
    }

    cout << answer << '\n';
    return 0;
}
