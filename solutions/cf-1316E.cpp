#include <algorithm>
#include <cstdint>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

struct Candidate {
    int64_t audience_strength;
    vector<int64_t> position_strength;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int candidate_count;
    int position_count;
    int audience_count;
    cin >> candidate_count >> position_count >> audience_count;

    vector<Candidate> candidates(candidate_count);
    for (Candidate& candidate : candidates) {
        cin >> candidate.audience_strength;
    }
    for (Candidate& candidate : candidates) {
        candidate.position_strength.resize(position_count);
        for (int position = 0; position < position_count; ++position) {
            cin >> candidate.position_strength[position];
        }
    }

    // Sort by audience value.  Along any fixed choice of position players,
    // the best audience is then simply the first k unassigned candidates.
    sort(candidates.begin(), candidates.end(), [](const Candidate& left,
                                                   const Candidate& right) {
        return left.audience_strength > right.audience_strength;
    });

    const int state_count = 1 << position_count;
    const int64_t IMPOSSIBLE = numeric_limits<int64_t>::lowest() / 4;

    // dp[mask] is the best score after the candidates processed so far, where
    // mask records exactly which playing positions have already been filled.
    // Rolling arrays keep memory at O(2^p) instead of O(n * 2^p).
    vector<int64_t> dp(state_count, IMPOSSIBLE);
    vector<int64_t> next_dp(state_count, IMPOSSIBLE);
    dp[0] = 0;

    for (int processed = 0; processed < candidate_count; ++processed) {
        fill(next_dp.begin(), next_dp.end(), IMPOSSIBLE);

        for (int mask = 0; mask < state_count; ++mask) {
            if (dp[mask] == IMPOSSIBLE) {
                continue;
            }

            const int assigned_players = __builtin_popcount(mask);
            const int unassigned_so_far = processed - assigned_players;

            // Do not use this candidate as a player.  If fewer than k earlier
            // nonplayers exist, this candidate belongs to the optimal audience
            // prefix and contributes audience strength.  Once k are chosen,
            // every later nonplayer is simply skipped.
            const int64_t audience_gain =
                unassigned_so_far < audience_count
                    ? candidates[processed].audience_strength
                    : 0;
            next_dp[mask] = max(
                next_dp[mask],
                dp[mask] + audience_gain
            );

            // Or assign this candidate to any still-empty playing position.
            // A person cannot be both audience and player because both choices
            // come from the same old state and enter separate next states.
            for (int position = 0; position < position_count; ++position) {
                const int position_bit = 1 << position;
                if ((mask & position_bit) != 0) {
                    continue;
                }

                next_dp[mask | position_bit] = max(
                    next_dp[mask | position_bit],
                    dp[mask] + candidates[processed].position_strength[position]
                );
            }
        }

        dp.swap(next_dp);
    }

    cout << dp[state_count - 1] << '\n';
    return 0;
}
