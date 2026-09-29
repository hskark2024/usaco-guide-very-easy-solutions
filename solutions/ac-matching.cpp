#include <cstdint>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    constexpr int MODULO = 1'000'000'007;

    int person_count;
    cin >> person_count;

    // compatible[man] is a bitmask of every woman who can be paired with him.
    // Keeping the row as bits lets a transition skip all incompatible choices.
    vector<uint32_t> compatible(person_count, 0);
    for (int man = 0; man < person_count; ++man) {
        for (int woman = 0; woman < person_count; ++woman) {
            int can_pair;
            cin >> can_pair;
            if (can_pair == 1) {
                compatible[man] |= uint32_t{1} << woman;
            }
        }
    }

    const uint32_t state_count = uint32_t{1} << person_count;

    // dp[mask] counts partial matchings in which exactly the women in mask
    // have been used.  The number of set bits also tells us exactly how many
    // men have been handled, so a second DP dimension is unnecessary.
    vector<int> dp(state_count, 0);

    // There is one way to pair nobody with nobody: choose nothing.
    dp[0] = 1;

    for (uint32_t mask = 0; mask < state_count; ++mask) {
        const int man = __builtin_popcount(mask);

        // A full mask already represents a complete matching.  There is no
        // next man, so it has no outgoing transition.
        if (man == person_count || dp[mask] == 0) {
            continue;
        }

        // Only women compatible with this man and absent from mask are legal.
        uint32_t available = compatible[man] & ~mask;
        while (available != 0) {
            // Extract one available woman, then erase her bit from the loop.
            const uint32_t woman_bit = available & -available;
            available ^= woman_bit;

            const uint32_t next_mask = mask | woman_bit;
            dp[next_mask] += dp[mask];
            if (dp[next_mask] >= MODULO) {
                dp[next_mask] -= MODULO;
            }
        }
    }

    cout << dp[state_count - 1] << '\n';
    return 0;
}
