#include <algorithm>
#include <cmath>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

// Codeforces 13E: Holes
//
// Every jump moves strictly to the right, so the path never cycles.  A direct
// query can still visit O(N) holes, however.  We split the row into blocks and
// summarize the entire path segment that stays inside each block.
class HoleJumps {
public:
    explicit HoleJumps(vector<int> initial_power)
        : n(static_cast<int>(initial_power.size()) - 1),
          block_size(static_cast<int>(sqrt(n)) + 1),
          power(std::move(initial_power)),
          next_outside(n + 1),
          jump_count(n + 1),
          last_inside(n + 1) {
        // Rebuilding every block once costs O(N) overall.
        for (int block = 0; block * block_size < n; ++block) {
            rebuild_block(block);
        }
    }

    void update(int hole, int new_power) {
        power[hole] = new_power;

        // Only summaries that begin in this block can depend on the changed
        // hole.  Later blocks are never reached while moving backward, and
        // earlier blocks deliberately stop their summary at this boundary.
        rebuild_block((hole - 1) / block_size);
    }

    pair<int, int> query(int start) const {
        int current = start;
        int total_jumps = 0;
        int final_hole = start;

        // Each iteration consumes every jump inside one block at once.
        while (current <= n) {
            total_jumps += jump_count[current];
            final_hole = last_inside[current];
            current = next_outside[current];
        }
        return {final_hole, total_jumps};
    }

private:
    int n;
    int block_size;
    vector<int> power;

    // For a path beginning at i:
    //   next_outside[i] = first destination outside i's current block;
    //   jump_count[i]   = jumps used to reach that destination;
    //   last_inside[i]  = last visited hole before that destination.
    vector<int> next_outside;
    vector<int> jump_count;
    vector<int> last_inside;

    void rebuild_block(int block) {
        const int left = block * block_size + 1;
        const int right = min(n, (block + 1) * block_size);

        // Jumps only go right, so processing from right to left guarantees
        // that a same-block destination already has a valid summary.
        for (int hole = right; hole >= left; --hole) {
            const int destination = hole + power[hole];

            if (destination > n || destination > right) {
                // One jump immediately leaves this block (and may leave the
                // complete row).  The current hole is the last one visited in
                // this block.
                next_outside[hole] = destination;
                jump_count[hole] = 1;
                last_inside[hole] = hole;
            } else {
                // The first jump remains in the block.  Splice it onto the
                // already-computed summary beginning at destination.
                next_outside[hole] = next_outside[destination];
                jump_count[hole] = 1 + jump_count[destination];
                last_inside[hole] = last_inside[destination];
            }
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int hole_count, move_count;
    cin >> hole_count >> move_count;

    vector<int> power(hole_count + 1);
    for (int hole = 1; hole <= hole_count; ++hole) {
        cin >> power[hole];
    }

    HoleJumps game(std::move(power));
    while (move_count--) {
        int type, hole;
        cin >> type >> hole;

        if (type == 0) {
            int new_power;
            cin >> new_power;
            game.update(hole, new_power);
        } else {
            const auto [last_hole, jumps] = game.query(hole);
            cout << last_hole << ' ' << jumps << '\n';
        }
    }
    return 0;
}
