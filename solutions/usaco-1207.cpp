#include <chrono>
#include <cstdint>
#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>
using namespace std;

using int64 = long long;
using Point = pair<int64, int64>;

// A hardened hash keeps the expected O(1) map operations dependable even for
// coordinate patterns that would be unfriendly to a simple xor hash.
struct PointHash {
    static uint64_t splitmix64(uint64_t value) {
        value += 0x9e3779b97f4a7c15ULL;
        value = (value ^ (value >> 30)) * 0xbf58476d1ce4e5b9ULL;
        value = (value ^ (value >> 27)) * 0x94d049bb133111ebULL;
        return value ^ (value >> 31);
    }

    size_t operator()(const Point &point) const {
        static const uint64_t seed =
            chrono::steady_clock::now().time_since_epoch().count();
        const uint64_t first = splitmix64(static_cast<uint64_t>(point.first) + seed);
        const uint64_t second = splitmix64(static_cast<uint64_t>(point.second) + seed);
        return static_cast<size_t>(first ^ (second + 0x9e3779b97f4a7c15ULL
                                            + (first << 6) + (first >> 2)));
    }
};

using FrequencyMap = unordered_map<Point, int64, PointHash>;

// Enumerate right-half subsets and group equal destinations by subset size.
// Storing a frequency instead of every repeated point saves work later.
static void build_right_frequencies(const vector<Point> &moves, int index,
                                    int used, int64 x, int64 y,
                                    vector<FrequencyMap> &frequencies) {
    if (index == static_cast<int>(moves.size())) {
        ++frequencies[used][{x, y}];
        return;
    }

    // Branch 1: skip this instruction.
    build_right_frequencies(moves, index + 1, used, x, y, frequencies);

    // Branch 2: use it exactly once.
    build_right_frequencies(moves, index + 1, used + 1,
                            x + moves[index].first,
                            y + moves[index].second, frequencies);
}

// Enumerate each left-half subset.  For every possible right subset size,
// look up the exact displacement needed to finish at the goal.
static void match_left_subsets(const vector<Point> &moves, int index, int used,
                               int64 x, int64 y, const Point &goal,
                               const vector<FrequencyMap> &right_frequencies,
                               vector<int64> &answer) {
    if (index == static_cast<int>(moves.size())) {
        const Point needed = {goal.first - x, goal.second - y};
        for (int right_used = 0;
             right_used < static_cast<int>(right_frequencies.size());
             ++right_used) {
            auto found = right_frequencies[right_used].find(needed);
            if (found != right_frequencies[right_used].end()) {
                answer[used + right_used] += found->second;
            }
        }
        return;
    }

    match_left_subsets(moves, index + 1, used, x, y, goal,
                       right_frequencies, answer);
    match_left_subsets(moves, index + 1, used + 1,
                       x + moves[index].first,
                       y + moves[index].second, goal,
                       right_frequencies, answer);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int instruction_count;
    cin >> instruction_count;

    Point goal;
    cin >> goal.first >> goal.second;

    vector<Point> all_moves(instruction_count);
    for (Point &move : all_moves) cin >> move.first >> move.second;

    // Split into halves so each recursive enumeration has at most 2^20 leaves.
    const int middle = instruction_count / 2;
    vector<Point> left_moves(all_moves.begin(), all_moves.begin() + middle);
    vector<Point> right_moves(all_moves.begin() + middle, all_moves.end());

    vector<FrequencyMap> right_frequencies(right_moves.size() + 1);

    // Reserve approximately C(right_size, k) buckets for each group.  This
    // avoids repeated rehashing; collisions in destination coordinates only
    // make the actual number of keys smaller.
    int64 combinations = 1;
    const int right_size = static_cast<int>(right_moves.size());
    for (int used = 0; used <= right_size; ++used) {
        right_frequencies[used].reserve(static_cast<size_t>(combinations));
        if (used < right_size) {
            combinations = combinations * (right_size - used) / (used + 1);
        }
    }

    build_right_frequencies(right_moves, 0, 0, 0, 0, right_frequencies);

    vector<int64> answer(instruction_count + 1, 0);
    match_left_subsets(left_moves, 0, 0, 0, 0, goal,
                       right_frequencies, answer);

    // The problem asks only for nonempty selections of sizes 1 through N.
    for (int used = 1; used <= instruction_count; ++used) {
        cout << answer[used] << '\n';
    }
    return 0;
}
