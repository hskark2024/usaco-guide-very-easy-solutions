#include <algorithm>
#include <iostream>
#include <tuple>
#include <vector>
using namespace std;

// CSES 2081: Fixed-Length Paths II
//
// This is the range version of centroid path counting.  Around one centroid,
// all endpoints are grouped by their distance from it.  A path through the
// centroid has length depth(a) + depth(b).  Count pairs in the requested range
// among all groups, subtract the pairs whose endpoints are in the same group,
// remove the centroid, and repeat on the smaller components.
class RangedPathCounter {
  public:
    RangedPathCounter(vector<vector<int>> graph, int minimum_length,
                      int maximum_length)
        : graph_(std::move(graph)), minimum_(minimum_length), maximum_(maximum_length),
          removed_(graph_.size(), false), parent_(graph_.size()),
          subtree_size_(graph_.size()) {}

    long long solve() {
        decompose(1);
        return answer_;
    }

  private:
    vector<vector<int>> graph_;
    int minimum_;
    int maximum_;
    vector<bool> removed_;
    vector<int> parent_;
    vector<int> subtree_size_;
    long long answer_ = 0;

    int find_centroid(int entry) {
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
        return -1;
    }

    vector<long long> collect_depth_counts(int start, int centroid) {
        vector<long long> counts(1, 0);
        vector<tuple<int, int, int>> stack = {{start, centroid, 1}};
        while (!stack.empty()) {
            const auto [vertex, parent, depth] = stack.back();
            stack.pop_back();

            // A deeper vertex cannot be in a path of length at most maximum_,
            // because the other endpoint always contributes a nonnegative depth.
            if (depth > maximum_) continue;
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

    static long long pairs_with_sum_at_most(
        const vector<long long> &counts, int limit) {
        if (limit < 0) return 0;

        // Prefix counts answer: how many possible second endpoints have depth
        // in (depth, limit-depth]?  The strict lower bound makes each unordered
        // pair appear once; equal-depth pairs are handled with n choose 2.
        vector<long long> prefix(counts.size() + 1, 0);
        for (size_t depth = 0; depth < counts.size(); ++depth) {
            prefix[depth + 1] = prefix[depth] + counts[depth];
        }

        long long result = 0;
        for (int depth = 0; depth < static_cast<int>(counts.size()); ++depth) {
            const int farthest = min(
                static_cast<int>(counts.size()) - 1, limit - depth);
            if (farthest < depth) break;

            if (2 * depth <= limit) {
                result += counts[depth] * (counts[depth] - 1) / 2;
            }
            if (farthest > depth) {
                const long long deeper_count =
                    prefix[farthest + 1] - prefix[depth + 1];
                result += counts[depth] * deeper_count;
            }
        }
        return result;
    }

    long long pairs_in_range(const vector<long long> &counts) const {
        return pairs_with_sum_at_most(counts, maximum_) -
               pairs_with_sum_at_most(counts, minimum_ - 1);
    }

    void decompose(int entry) {
        const int centroid = find_centroid(entry);
        vector<long long> all_counts(1, 1);  // The centroid has depth zero.

        for (const int next : graph_[centroid]) {
            if (removed_[next]) continue;
            vector<long long> group = collect_depth_counts(next, centroid);
            answer_ -= pairs_in_range(group);

            if (all_counts.size() < group.size()) {
                all_counts.resize(group.size(), 0);
            }
            for (size_t depth = 1; depth < group.size(); ++depth) {
                all_counts[depth] += group[depth];
            }
        }
        answer_ += pairs_in_range(all_counts);

        removed_[centroid] = true;
        for (const int next : graph_[centroid]) {
            if (!removed_[next]) decompose(next);
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int node_count, minimum_length, maximum_length;
    cin >> node_count >> minimum_length >> maximum_length;
    vector<vector<int>> graph(node_count + 1);
    for (int edge = 1; edge < node_count; ++edge) {
        int first, second;
        cin >> first >> second;
        graph[first].push_back(second);
        graph[second].push_back(first);
    }

    RangedPathCounter counter(
        std::move(graph), minimum_length, maximum_length);
    cout << counter.solve() << '\n';
    return 0;
}
