#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

// Codeforces 1299C: Water Balance
//
// The lexicographically smallest reachable sequence is nondecreasing and is
// constant on contiguous averaged blocks.  Pool Adjacent Violators builds
// exactly those blocks: whenever two neighboring averages decrease, they must
// be replaced by their combined average.
struct Block {
    long long sum;
    int length;
};

static bool average_is_greater(const Block &left, const Block &right) {
    // Compare left.sum / left.length and right.sum / right.length without
    // floating-point rounding.  The products fit in 64 bits for the official
    // limits, but __int128 makes that safety explicit.
    return static_cast<__int128>(left.sum) * right.length >
           static_cast<__int128>(right.sum) * left.length;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int tank_count;
    cin >> tank_count;

    vector<Block> blocks;
    blocks.reserve(tank_count);

    for (int index = 0; index < tank_count; ++index) {
        long long water;
        cin >> water;

        // Begin with one block per tank.  This represents its original amount.
        blocks.push_back({water, 1});

        // A decreasing pair cannot appear in the final answer.  Pooling the
        // pair preserves its total water and gives the smallest possible value
        // at the beginning of their combined interval.  One merge can expose a
        // new violation to its left, so continue until averages are ordered.
        while (blocks.size() >= 2 &&
               average_is_greater(blocks[blocks.size() - 2], blocks.back())) {
            const Block right = blocks.back();
            blocks.pop_back();
            blocks.back().sum += right.sum;
            blocks.back().length += right.length;
        }
    }

    cout << fixed << setprecision(10);
    for (const Block &block : blocks) {
        const long double average =
            static_cast<long double>(block.sum) / block.length;

        // Every tank in a pooled interval receives the same average amount.
        for (int repeat = 0; repeat < block.length; ++repeat) {
            cout << average << '\n';
        }
    }
    return 0;
}
