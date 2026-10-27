#include <iostream>
#include <string>
#include <vector>
using namespace std;

// A two-dimensional Fenwick tree is the grid version of the familiar 1D
// Fenwick tree. Each cell contributes to logarithmically many rectangular
// summaries, which supports both point changes and prefix-rectangle sums.
class Fenwick2D {
public:
    explicit Fenwick2D(const vector<string> &grid)
        : size_(static_cast<int>(grid.size())),
          tree_(size_ + 1, vector<int>(size_ + 1, 0)) {
        // First copy individual tree indicators into one-based storage.
        for (int y = 1; y <= size_; ++y) {
            for (int x = 1; x <= size_; ++x) {
                tree_[y][x] = (grid[y - 1][x - 1] == '*');
            }
        }

        // Build each row as a 1D Fenwick tree, then build the y direction.
        // This is O(N^2), avoiding N^2 separate O(log^2 N) insertions.
        for (int y = 1; y <= size_; ++y) {
            for (int x = 1; x <= size_; ++x) {
                const int parent_x = x + (x & -x);
                if (parent_x <= size_) {
                    tree_[y][parent_x] += tree_[y][x];
                }
            }
        }
        for (int y = 1; y <= size_; ++y) {
            const int parent_y = y + (y & -y);
            if (parent_y <= size_) {
                for (int x = 1; x <= size_; ++x) {
                    tree_[parent_y][x] += tree_[y][x];
                }
            }
        }
    }

    void add(int y, int x, int delta) {
        for (int current_y = y; current_y <= size_;
             current_y += current_y & -current_y) {
            for (int current_x = x; current_x <= size_;
                 current_x += current_x & -current_x) {
                tree_[current_y][current_x] += delta;
            }
        }
    }

    int rectangle_sum(int y1, int x1, int y2, int x2) const {
        // Inclusion-exclusion keeps the desired bottom-right rectangle and
        // removes the two strips outside it, then restores their overlap.
        return prefix_sum(y2, x2)
               - prefix_sum(y1 - 1, x2)
               - prefix_sum(y2, x1 - 1)
               + prefix_sum(y1 - 1, x1 - 1);
    }

private:
    int size_;
    vector<vector<int>> tree_;

    int prefix_sum(int y, int x) const {
        int result = 0;
        for (int current_y = y; current_y > 0;
             current_y -= current_y & -current_y) {
            for (int current_x = x; current_x > 0;
                 current_x -= current_x & -current_x) {
                result += tree_[current_y][current_x];
            }
        }
        return result;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int size, query_count;
    cin >> size >> query_count;

    vector<string> grid(size);
    for (string &row : grid) {
        cin >> row;
    }

    Fenwick2D fenwick(grid);
    while (query_count--) {
        int type;
        cin >> type;
        if (type == 1) {
            int y, x;
            cin >> y >> x;

            // Remember the literal grid state so a toggle knows whether its
            // numeric Fenwick update is +1 or -1.
            const int delta = (grid[y - 1][x - 1] == '.') ? 1 : -1;
            grid[y - 1][x - 1] = (delta == 1) ? '*' : '.';
            fenwick.add(y, x, delta);
        } else {
            int y1, x1, y2, x2;
            cin >> y1 >> x1 >> y2 >> x2;
            cout << fenwick.rectangle_sum(y1, x1, y2, x2) << '\n';
        }
    }

    return 0;
}
