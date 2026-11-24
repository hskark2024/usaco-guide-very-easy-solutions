#include <algorithm>
#include <iostream>
#include <tuple>
#include <vector>
using namespace std;

// USACO 2013 US Open Gold: Yin and Yang
//
// Give the two edge colors weights +1 and -1.  A route is balanced exactly
// when its weight sum is zero.  It has a legal rest stop when an internal
// vertex splits it into two zero-sum pieces.
//
// At one centroid, consider paths that use that centroid.  For every vertex v,
// let balance(v) be the sum from the centroid to v.  Two vertices in different
// centroid branches form a zero-sum route when their balances are opposites.
// The route has a rest stop if either endpoint's balance already appeared at
// an earlier vertex on its centroid path.  Balance zero is special: for two
// different branches, the centroid itself is a legal rest stop.
//
// We merge branches one at a time.  Histograms count all opposite balances and
// subtract the pairs for which neither side has a repeated balance.  Centroid
// decomposition makes every unordered path belong to exactly one such step.
class BalancedPathCounter {
  public:
    struct Edge {
        int to;
        int weight;
    };

    explicit BalancedPathCounter(vector<vector<Edge>> graph)
        : graph_(std::move(graph)), node_count_(graph_.size() - 1),
          removed_(node_count_ + 1, false), parent_(node_count_ + 1),
          subtree_size_(node_count_ + 1),
          path_frequency_(2 * node_count_ + 1, 0),
          total_by_balance_(2 * node_count_ + 1, 0),
          bad_by_balance_(2 * node_count_ + 1, 0) {}

    long long solve() {
        decompose(1);
        return answer_;
    }

  private:
    struct PathInfo {
        int balance;
        bool repeats_before_centroid;
        bool has_rest_for_cross_path;
    };

    vector<vector<Edge>> graph_;
    int node_count_;
    vector<bool> removed_;
    vector<int> parent_;
    vector<int> subtree_size_;
    vector<int> path_frequency_;
    vector<long long> total_by_balance_;
    vector<long long> bad_by_balance_;
    long long answer_ = 0;

    int index_of(int balance) const { return balance + node_count_; }

    int find_centroid(int entry) {
        // Root the current active component iteratively.  This avoids a stack
        // overflow on the official 100,000-node chain case.
        vector<int> component = {entry};
        parent_[entry] = 0;
        for (size_t index = 0; index < component.size(); ++index) {
            const int vertex = component[index];
            for (const Edge edge : graph_[vertex]) {
                if (removed_[edge.to] || edge.to == parent_[vertex]) continue;
                parent_[edge.to] = vertex;
                component.push_back(edge.to);
            }
        }

        // Children are processed before parents, so subtree sizes are exact.
        for (auto iterator = component.rbegin(); iterator != component.rend();
             ++iterator) {
            const int vertex = *iterator;
            subtree_size_[vertex] = 1;
            for (const Edge edge : graph_[vertex]) {
                if (!removed_[edge.to] && parent_[edge.to] == vertex) {
                    subtree_size_[vertex] += subtree_size_[edge.to];
                }
            }
        }

        const int component_size = static_cast<int>(component.size());
        for (const int vertex : component) {
            int largest_piece = component_size - subtree_size_[vertex];
            for (const Edge edge : graph_[vertex]) {
                if (!removed_[edge.to] && parent_[edge.to] == vertex) {
                    largest_piece = max(largest_piece, subtree_size_[edge.to]);
                }
            }
            if (2 * largest_piece <= component_size) return vertex;
        }
        return -1;
    }

    vector<PathInfo> collect_branch(int start, int centroid,
                                    int first_weight) {
        // An enter/exit DFS maintains frequencies only on the current root-to-
        // vertex path.  The centroid's zero is deliberately not inserted:
        // that lets us distinguish a genuinely internal zero from the start.
        struct Event {
            int vertex;
            int parent;
            int balance;
            bool exiting;
        };

        vector<PathInfo> result;
        vector<Event> stack = {{start, centroid, first_weight, false}};
        while (!stack.empty()) {
            const Event event = stack.back();
            stack.pop_back();
            const int balance_index = index_of(event.balance);

            if (event.exiting) {
                --path_frequency_[balance_index];
                continue;
            }

            // A prior equal prefix makes the segment from that prior vertex to
            // this endpoint balanced.  For cross-branch paths, balance zero
            // also makes the centroid itself a valid internal rest stop.
            const bool repeats = path_frequency_[balance_index] > 0;
            result.push_back(
                {event.balance, repeats, repeats || event.balance == 0});

            ++path_frequency_[balance_index];
            stack.push_back(
                {event.vertex, event.parent, event.balance, true});
            for (const Edge edge : graph_[event.vertex]) {
                if (removed_[edge.to] || edge.to == event.parent) continue;
                stack.push_back({edge.to, event.vertex,
                                 event.balance + edge.weight, false});
            }
        }
        return result;
    }

    void count_paths_through(int centroid) {
        vector<int> touched_balances;

        for (const Edge first_edge : graph_[centroid]) {
            if (removed_[first_edge.to]) continue;
            const vector<PathInfo> branch =
                collect_branch(first_edge.to, centroid, first_edge.weight);

            // Query only previously merged branches, so same-branch paths are
            // postponed to a later centroid and unordered pairs appear once.
            for (const PathInfo info : branch) {
                const int opposite_index = index_of(-info.balance);
                answer_ += total_by_balance_[opposite_index];
                if (!info.has_rest_for_cross_path) {
                    // Both endpoints without a repeated prefix are invalid.
                    answer_ -= bad_by_balance_[opposite_index];
                }

                // If the centroid is one endpoint, it cannot also be the rest
                // stop.  We therefore require a repeated zero at a genuinely
                // internal vertex, not merely the centroid's initial zero.
                if (info.balance == 0 && info.repeats_before_centroid) {
                    ++answer_;
                }
            }

            // Merge this branch only after all of its queries are complete.
            for (const PathInfo info : branch) {
                const int balance_index = index_of(info.balance);
                if (total_by_balance_[balance_index] == 0) {
                    touched_balances.push_back(info.balance);
                }
                ++total_by_balance_[balance_index];
                if (!info.has_rest_for_cross_path) {
                    ++bad_by_balance_[balance_index];
                }
            }
        }

        // Clear only the histogram cells used at this centroid.
        for (const int balance : touched_balances) {
            total_by_balance_[index_of(balance)] = 0;
            bad_by_balance_[index_of(balance)] = 0;
        }
    }

    void decompose(int entry) {
        const int centroid = find_centroid(entry);
        count_paths_through(centroid);
        removed_[centroid] = true;

        // Each recursive component is at most half as large, so only this
        // decomposition recursion remains and its depth is logarithmic.
        for (const Edge edge : graph_[centroid]) {
            if (!removed_[edge.to]) decompose(edge.to);
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int node_count;
    cin >> node_count;
    vector<vector<BalancedPathCounter::Edge>> graph(node_count + 1);
    for (int edge_index = 1; edge_index < node_count; ++edge_index) {
        int first, second, type;
        cin >> first >> second >> type;
        // Only equality of the two color counts matters, so either color may
        // be +1.  The other receives -1.
        const int weight = (type == 0 ? 1 : -1);
        graph[first].push_back({second, weight});
        graph[second].push_back({first, weight});
    }

    BalancedPathCounter counter(std::move(graph));
    cout << counter.solve() << '\n';
    return 0;
}
