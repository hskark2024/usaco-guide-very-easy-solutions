#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

// After rotating the plane, every reachable Manhattan diamond becomes an
// axis-aligned square.  While a two-pointer window handles the square's first
// coordinate, this lazy segment tree finds the best second coordinate.
class RangeAddMaximumTree {
public:
    explicit RangeAddMaximumTree(int size)
        : size_(size), maximum_(4 * size, 0), lazy_add_(4 * size, 0) {}

    void add(int query_left, int query_right, long long amount) {
        add(1, 0, size_ - 1, query_left, query_right, amount);
    }

    long long maximum() const {
        // The root always summarizes every compressed candidate coordinate.
        return maximum_[1];
    }

private:
    int size_;
    vector<long long> maximum_;
    vector<long long> lazy_add_;

    void apply(int node, long long amount) {
        maximum_[node] += amount;
        lazy_add_[node] += amount;
    }

    void push(int node) {
        if (lazy_add_[node] == 0) {
            return;
        }
        apply(node * 2, lazy_add_[node]);
        apply(node * 2 + 1, lazy_add_[node]);
        lazy_add_[node] = 0;
    }

    void add(int node, int left, int right,
             int query_left, int query_right, long long amount) {
        if (query_right < left || right < query_left) {
            return;
        }
        if (query_left <= left && right <= query_right) {
            apply(node, amount);
            return;
        }

        push(node);
        const int middle = (left + right) / 2;
        add(node * 2, left, middle, query_left, query_right, amount);
        add(node * 2 + 1, middle + 1, right,
            query_left, query_right, amount);
        maximum_[node] = max(maximum_[node * 2], maximum_[node * 2 + 1]);
    }
};

struct Patch {
    long long grass;
    long long u;  // x + y
    long long v;  // x - y
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // The official judge uses files, while repository tests use standard I/O.
    if (FILE *input_file = fopen("lazy.in", "r")) {
        fclose(input_file);
        freopen("lazy.in", "r", stdin);
        freopen("lazy.out", "w", stdout);
    }

    int patch_count;
    long long step_limit;
    cin >> patch_count >> step_limit;

    vector<Patch> patches(patch_count);
    vector<long long> candidate_v;
    candidate_v.reserve(2 * patch_count);

    for (Patch &patch : patches) {
        long long x, y;
        cin >> patch.grass >> x >> y;
        patch.u = x + y;
        patch.v = x - y;

        // This patch is reachable exactly when the transformed center's v
        // coordinate lies in this closed interval.
        candidate_v.push_back(patch.v - step_limit);
        candidate_v.push_back(patch.v + step_limit);
    }

    sort(patches.begin(), patches.end(), [](const Patch &a, const Patch &b) {
        return a.u < b.u;
    });
    sort(candidate_v.begin(), candidate_v.end());
    candidate_v.erase(unique(candidate_v.begin(), candidate_v.end()),
                      candidate_v.end());

    RangeAddMaximumTree tree(static_cast<int>(candidate_v.size()));

    auto change_patch = [&](const Patch &patch, long long signed_grass) {
        // Add this patch's weight to every transformed center that can reach
        // it in the v direction. Both endpoints matter because reachability
        // uses distance <= K.
        const int left = static_cast<int>(lower_bound(
            candidate_v.begin(), candidate_v.end(), patch.v - step_limit)
            - candidate_v.begin());
        const int right = static_cast<int>(lower_bound(
            candidate_v.begin(), candidate_v.end(), patch.v + step_limit)
            - candidate_v.begin());
        tree.add(left, right, signed_grass);
    };

    long long answer = 0;
    int left = 0;
    for (int right = 0; right < patch_count; ++right) {
        change_patch(patches[right], patches[right].grass);

        // A transformed square has width 2K. Remove exactly the patches that
        // can no longer share such a square with the current right endpoint.
        while (patches[right].u - patches[left].u > 2 * step_limit) {
            change_patch(patches[left], -patches[left].grass);
            ++left;
        }

        answer = max(answer, tree.maximum());
    }

    cout << answer << '\n';
    return 0;
}
