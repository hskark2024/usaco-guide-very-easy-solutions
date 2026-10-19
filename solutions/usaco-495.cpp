#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
using namespace std;

struct Point {
    int x;
    int y;
};

long long manhattan_distance(const Point &first, const Point &second) {
    return llabs(static_cast<long long>(first.x) - second.x)
         + llabs(static_cast<long long>(first.y) - second.y);
}

class SumAndMaximumTrees {
public:
    explicit SumAndMaximumTrees(int element_count) {
        leaf_count_ = 1;
        while (leaf_count_ < element_count) leaf_count_ *= 2;
        sums_.assign(2 * leaf_count_, 0);
        maximums_.assign(2 * leaf_count_, 0);
    }

    void set_sum(int index, long long value) {
        int node = leaf_count_ + index;
        sums_[node] = value;
        for (node /= 2; node >= 1; node /= 2) {
            sums_[node] = sums_[2 * node] + sums_[2 * node + 1];
        }
    }

    void set_maximum(int index, long long value) {
        int node = leaf_count_ + index;
        maximums_[node] = value;
        for (node /= 2; node >= 1; node /= 2) {
            maximums_[node] = max(maximums_[2 * node], maximums_[2 * node + 1]);
        }
    }

    long long range_sum(int left, int right) const {
        long long result = 0;
        for (left += leaf_count_, right += leaf_count_; left < right;
             left /= 2, right /= 2) {
            if (left & 1) result += sums_[left++];
            if (right & 1) result += sums_[--right];
        }
        return result;
    }

    long long range_maximum(int left, int right) const {
        long long result = 0;
        for (left += leaf_count_, right += leaf_count_; left < right;
             left /= 2, right /= 2) {
            if (left & 1) result = max(result, maximums_[left++]);
            if (right & 1) result = max(result, maximums_[--right]);
        }
        return result;
    }

private:
    int leaf_count_ = 1;
    vector<long long> sums_;
    vector<long long> maximums_;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Preserve the contest file interface when marathon.in exists, but let
    // repository tests and most online judges use standard input normally.
    if (FILE *file = fopen("marathon.in", "r")) {
        fclose(file);
        freopen("marathon.in", "r", stdin);
        freopen("marathon.out", "w", stdout);
    }

    int checkpoint_count, operation_count;
    cin >> checkpoint_count >> operation_count;
    vector<Point> checkpoints(checkpoint_count);
    for (Point &point : checkpoints) cin >> point.x >> point.y;

    SumAndMaximumTrees trees(checkpoint_count);

    auto refresh_edge = [&](int left_index) {
        // Edge left_index joins checkpoint left_index to left_index + 1.
        if (0 <= left_index && left_index + 1 < checkpoint_count) {
            trees.set_sum(
                left_index,
                manhattan_distance(checkpoints[left_index], checkpoints[left_index + 1])
            );
        }
    };

    auto refresh_saving = [&](int middle_index) {
        // Skipping the middle replaces two edges with one direct edge. Store
        // exactly how much distance that choice saves; triangle inequality
        // guarantees the value is nonnegative.
        if (0 < middle_index && middle_index + 1 < checkpoint_count) {
            const long long saving =
                manhattan_distance(checkpoints[middle_index - 1], checkpoints[middle_index])
                + manhattan_distance(checkpoints[middle_index], checkpoints[middle_index + 1])
                - manhattan_distance(checkpoints[middle_index - 1], checkpoints[middle_index + 1]);
            trees.set_maximum(middle_index, saving);
        }
    };

    for (int edge = 0; edge + 1 < checkpoint_count; ++edge) refresh_edge(edge);
    for (int middle = 1; middle + 1 < checkpoint_count; ++middle) refresh_saving(middle);

    while (operation_count--) {
        char type;
        int first;
        cin >> type >> first;
        --first;

        if (type == 'U') {
            cin >> checkpoints[first].x >> checkpoints[first].y;

            // Moving one checkpoint changes at most two adjacent edge lengths
            // and the three skip savings whose triples contain that point.
            refresh_edge(first - 1);
            refresh_edge(first);
            refresh_saving(first - 1);
            refresh_saving(first);
            refresh_saving(first + 1);
        } else {
            int last;
            cin >> last;
            --last;

            // Edges [first,last) make the unskipped route. Only checkpoints
            // strictly inside the query may be skipped, so savings use
            // middle indices [first+1,last).
            const long long full_distance = trees.range_sum(first, last);
            const long long best_saving = trees.range_maximum(first + 1, last);
            cout << full_distance - best_saving << '\n';
        }
    }

    return 0;
}
