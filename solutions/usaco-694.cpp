#include <algorithm>
#include <array>
#include <cstdio>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

// We do not need to store Bessie's literal gesture.  State 0 means "use the
// gesture that beats Hoof," state 1 means "use the gesture that beats Paper,"
// and state 2 means "use the gesture that beats Scissors."  With this naming,
// a state wins exactly when its index matches Farmer John's encoded gesture.
int encode_opponent_gesture(char gesture) {
    if (gesture == 'H') {
        return 0;
    }
    if (gesture == 'P') {
        return 1;
    }
    return 2;  // The only remaining valid input is Scissors.
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // USACO uses files, while the fallback keeps local smoke tests convenient.
    if (FILE *input_file = fopen("hps.in", "r")) {
        fclose(input_file);
        freopen("hps.in", "r", stdin);
        freopen("hps.out", "w", stdout);
    }

    int game_count, switch_limit;
    cin >> game_count >> switch_limit;

    vector<int> opponent(game_count);
    for (int game = 0; game < game_count; ++game) {
        char gesture;
        cin >> gesture;
        opponent[game] = encode_opponent_gesture(gesture);
    }

    // previous[s][g] is the most games Bessie can have won after all games
    // processed so far, using exactly s switches and ending in gesture-state g.
    // A very negative sentinel separates impossible states from valid scores.
    const int IMPOSSIBLE = numeric_limits<int>::min() / 4;
    vector<array<int, 3>> previous(switch_limit + 1);
    for (auto &row : previous) {
        row.fill(IMPOSSIBLE);
    }

    // Before game 1, Bessie may choose any initial gesture for free.  Picking
    // that first gesture is not a switch, so all three zero-switch states start
    // at score zero.
    previous[0].fill(0);

    for (int game = 0; game < game_count; ++game) {
        vector<array<int, 3>> current(switch_limit + 1);
        for (auto &row : current) {
            row.fill(IMPOSSIBLE);
        }

        for (int switches = 0; switches <= switch_limit; ++switches) {
            for (int gesture = 0; gesture < 3; ++gesture) {
                // Option 1: keep yesterday's gesture.  No switch is spent.
                int best_before_this_game = previous[switches][gesture];

                // Option 2: change from either of the other two gestures.  The
                // previous state must then have used one fewer switch.
                if (switches > 0) {
                    for (int old_gesture = 0; old_gesture < 3; ++old_gesture) {
                        if (old_gesture != gesture) {
                            best_before_this_game = max(
                                best_before_this_game,
                                previous[switches - 1][old_gesture]
                            );
                        }
                    }
                }

                // Impossible states must not receive a fake win from adding 1.
                if (best_before_this_game == IMPOSSIBLE) {
                    continue;
                }

                // Exactly one gesture beats the opponent's move.  Our state
                // labels were chosen so equality identifies that gesture.
                const int win = (gesture == opponent[game]) ? 1 : 0;
                current[switches][gesture] = best_before_this_game + win;
            }
        }

        // Only the previous game is needed for the next transition, so rolling
        // the two tables reduces memory from O(NK) to O(K).
        previous.swap(current);
    }

    // The rule says "at most K" switches, so accept every reachable switch
    // count from zero through K and every possible final gesture.
    int answer = 0;
    for (int switches = 0; switches <= switch_limit; ++switches) {
        for (int gesture = 0; gesture < 3; ++gesture) {
            answer = max(answer, previous[switches][gesture]);
        }
    }

    cout << answer << '\n';
    return 0;
}
