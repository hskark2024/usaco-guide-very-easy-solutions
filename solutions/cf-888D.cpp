#include <array>
#include <iostream>

using namespace std;

// Returns "n choose r" exactly. Here r never exceeds 4, so evaluating the
// product directly is both simple and safely inside 64-bit integer range.
long long choose(int n, int r) {
    if (r < 0 || r > n) return 0;

    long long result = 1;
    for (int picked = 1; picked <= r; ++picked) {
        // At this step the division is exact because the partial product is
        // another binomial coefficient: C(n-r+picked, picked).
        result = result * (n - r + picked) / picked;
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    // derangements[m] is the number of permutations of m chosen positions in
    // which none of those positions keeps its original value. Only 0..4 are
    // necessary because the statement guarantees k <= 4.
    constexpr array<long long, 5> derangements = {1, 0, 1, 2, 9};

    long long answer = 0;
    for (int moved = 0; moved <= k; ++moved) {
        // First select exactly which positions will be incorrect.
        const long long chosen_positions = choose(n, moved);

        // Then derange the values among those positions. Requiring a
        // derangement is essential: otherwise some "moved" positions could
        // accidentally remain fixed and the same permutation would be counted
        // again under a smaller value of moved.
        answer += chosen_positions * derangements[moved];
    }

    cout << answer << '\n';
}
