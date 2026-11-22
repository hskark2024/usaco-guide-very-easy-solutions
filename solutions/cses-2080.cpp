#include <algorithm>
#include <iostream>
#include <tuple>
#include <vector>
using namespace std;

// CSES 2080: Fixed-Length Paths I
//
// Every path has one highest vertex in the centroid-decomposition tree.  At a
// chosen centroid, a path goes through that centroid exactly when its endpoints
// lie in different neighbor components (or one endpoint is the centroid).
// Depth histograms let us count endpoint pairs whose depths add to K.  We count
// all pairs around the centroid, then subtract pairs contained in one neighbor
// component.  Repeating after removing the centroid counts every path once.
class ExactPathCounter {
  public:
    ExactPathCounter(vector<vector<int>> graph, int target_length)
        : graph_(std::move(graph)), target_(target_length),
          removed_(graph_.size(), false), parent_(graph_.size()),
          subtree_size_(graph_.size()) {}

    long long solve() {
        decompose(1);
        return answer_;
    }

  private:
    vector<vector<int>> graph_;
    int target_;
    vector<bool> removed_;
    vector<int> parent_;
    vector<int> subtree_size_;
    long long answer_ = 0;

    int find_centroid(int entry) {
        // Collect this active component and make a temporary rooted tree.
        vector<int> component = {entry};
        parent_[entry] = 0;
        for (size_t index = 0; index < component.size(); ++index) {
            const int vertex = component[index];
            for (const int next : graph_[vertex]) {
                if (removed_[next] || next == parent_[vertex]) continue;
                parent_[next] = vertex;
                component.push_back(next);
            }
        }

        // Reverse order computes subtree sizes even if the original tree is a
        // 200,000-node chain; no call-stack depth depends on that shape.
        for (auto iterator = component.rbegin(); iterator != component.rend();
             ++iterator) {
            const int vertex = *iterator;
            subtree_size_[vertex] = 1;
            for (const int next : graph_[vertex]) {
                if (!removed_[next] && parent_[next] == vertex) {
                    subtree_size_[vertex] += subtree_size_[next];
                }
            }
        }

        const int component_size = static_cast<int>(component.size());
        for (const int vertex : component) {
            int largest_piece = component_size - subtree_size_[vertex];
            for (const int next : graph_[vertex]) {
                if (!removed_[next] && parent_[next] == vertex) {
                    largest_piece = max(largest_piece, subtree_size_[next]);
                }
            }
            if (2 * largest_piece <= component_size) return vertex;
        }
        return -1;  // Every nonempty tree has a centroid.
    }

    vector<long long> collect_depth_counts(int start, int centroid) {
        // counts[d] is the number of vertices in this one neighbor component
        // at distance d from the centroid.  Distances above K cannot form a
        // requested path, so pruning them saves work on long branches.
        vector<long long> counts(1, 0);
        vector<tuple<int, int, int>> stack = {{start, centroid, 1}};
        while (!stack.empty()) {
            const auto [vertex, parent, depth] = stack.back();
            stack.pop_back();
            if (depth > target_) continue;
            if (static_cast<int>(counts.size()) <= depth) {
                counts.resize(depth + 1, 0);
            }
            ++counts[depth];
            for (const int next : graph_[vertex]) {
                if (!removed_[next] && next != parent) {
                    stack.push_back({next, vertex, depth + 1});
                }
            }
        }
        return counts;
    }

    long long pairs_with_exact_sum(const vector<long long> &counts) const {
        long long result = 0;
        // Restrict depth <= complement so each unordered pair is counted once.
        for (int depth = 0; 2 * depth <= target_; ++depth) {
            const int other_depth = target_ - depth;
            if (depth >= static_cast<int>(counts.size()) ||
                other_depth >= static_cast<int>(counts.size())) {
                continue;
            }
            if (depth < other_depth) {
                result += counts[depth] * counts[other_depth];
            } else {
                result += counts[depth] * (counts[depth] - 1) / 2;
            }
        }
        return result;
    }

    void decompose(int entry) {
        const int centroid = find_centroid(entry);

        // The all-components histogram includes the centroid at depth zero.
        vector<long long> all_counts(1, 1);
        for (const int next : graph_[centroid]) {
            if (removed_[next]) continue;
            vector<long long> group = collect_depth_counts(next, centroid);

            // These pairs do not pass through this centroid, so remove them.
            answer_ -= pairs_with_exact_sum(group);

            if (all_counts.size() < group.size()) {
                all_counts.resize(group.size(), 0);
            }
            for (size_t depth = 1; depth < group.size(); ++depth) {
                all_counts[depth] += group[depth];
            }
        }
        answer_ += pairs_with_exact_sum(all_counts);

        removed_[centroid] = true;
        // Centroid recursion is only logarithmically deep because every new
        // component has at most half as many vertices as its parent component.
        for (const int next : graph_[centroid]) {
            if (!removed_[next]) decompose(next);
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int node_count, target_length;
    cin >> node_count >> target_length;
    vector<vector<int>> graph(node_count + 1);
    for (int edge = 1; edge < node_count; ++edge) {
        int first, second;
        cin >> first >> second;
        graph[first].push_back(second);
        graph[second].push_back(first);
    }

    ExactPathCounter counter(std::move(graph), target_length);
    cout << counter.solve() << '\n';
    return 0;
}
