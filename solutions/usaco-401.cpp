#include <algorithm>
#include <cstdio>
#include <iostream>
#include <limits>
#include <utility>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Keep the original USACO file interface when dec.in is present, while
    // still allowing the repository tests to use ordinary standard input.
    if (FILE *file = fopen("dec.in", "r")) {
        fclose(file);
        freopen("dec.in", "r", stdin);
        freopen("dec.out", "w", stdout);
    }

    int cow_count, bonus_count;
    cin >> cow_count >> bonus_count;

    // bonuses[k] contains the (required score, awarded points) rules checked
    // immediately after the first k events have been filled.
    vector<vector<pair<int, int>>> bonuses(cow_count + 1);
    for (int index = 0; index < bonus_count; ++index) {
        int event_count, required_score, award;
        cin >> event_count >> required_score >> award;
        bonuses[event_count].push_back({required_score, award});
    }

    // A cow is a row and an event is a column.
    vector<vector<int>> skill(cow_count, vector<int>(cow_count));
    for (int cow = 0; cow < cow_count; ++cow) {
        for (int event = 0; event < cow_count; ++event) {
            cin >> skill[cow][event];
        }
    }

    // Sorting by threshold is essential. An easier bonus can raise the score
    // enough to unlock another bonus for the same prefix of events.
    for (auto &event_bonuses : bonuses) {
        sort(event_bonuses.begin(), event_bonuses.end());
    }

    const int state_count = 1 << cow_count;
    const int unreachable = numeric_limits<int>::min() / 4;
    vector<int> best(state_count, unreachable);
    best[0] = 0;

    // mask tells us exactly which cows have already been assigned. Its number
    // of set bits also tells us which event must be filled next, so no second
    // DP dimension is necessary.
    for (int mask = 0; mask < state_count; ++mask) {
        if (best[mask] == unreachable) continue;

        const int event = __builtin_popcount(static_cast<unsigned>(mask));
        if (event == cow_count) continue;

        for (int cow = 0; cow < cow_count; ++cow) {
            if (mask & (1 << cow)) continue;  // Every cow is used once.

            const int next_mask = mask | (1 << cow);
            int score = best[mask] + skill[cow][event];

            // These bonuses are automatic. Because they are processed from
            // low threshold to high threshold, earlier awards are included in
            // the score tested by later rules, exactly as the statement asks.
            for (const auto &[required_score, award] : bonuses[event + 1]) {
                if (score >= required_score) score += award;
            }

            best[next_mask] = max(best[next_mask], score);
        }
    }

    cout << best.back() << '\n';
    return 0;
}
