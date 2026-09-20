#include <algorithm>
#include <cstdio>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

using namespace std;

struct Point {
    int x;
    int y;
};

Point take_step(Point position, char direction) {
    if (direction == 'N') ++position.y;
    if (direction == 'S') --position.y;
    if (direction == 'E') ++position.x;
    if (direction == 'W') --position.x;
    return position;
}

long long radio_cost(const Point &farmer, const Point &bessie) {
    const long long dx = farmer.x - bessie.x;
    const long long dy = farmer.y - bessie.y;
    return dx * dx + dy * dy;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Support both the original USACO file interface and repository tests.
    if (FILE *input_file = fopen("radio.in", "r")) {
        fclose(input_file);
        freopen("radio.in", "r", stdin);
        freopen("radio.out", "w", stdout);
    }

    int farmer_steps, bessie_steps;
    cin >> farmer_steps >> bessie_steps;

    vector<Point> farmer_positions(farmer_steps + 1);
    vector<Point> bessie_positions(bessie_steps + 1);
    cin >> farmer_positions[0].x >> farmer_positions[0].y;
    cin >> bessie_positions[0].x >> bessie_positions[0].y;

    string farmer_path, bessie_path;
    cin >> farmer_path >> bessie_path;

    // Prefix positions let every DP transition get the current separation in
    // O(1), instead of replaying movement strings many times.
    for (int i = 1; i <= farmer_steps; ++i) {
        farmer_positions[i] = take_step(farmer_positions[i - 1], farmer_path[i - 1]);
    }
    for (int j = 1; j <= bessie_steps; ++j) {
        bessie_positions[j] = take_step(bessie_positions[j - 1], bessie_path[j - 1]);
    }

    const long long INF = numeric_limits<long long>::max() / 4;

    // previous[j] is the minimum energy once Farmer has completed i-1 moves
    // and Bessie has completed j.  current builds the row for i Farmer moves.
    // The two may advance separately or together during one time step.
    vector<long long> previous(bessie_steps + 1, INF);
    vector<long long> current(bessie_steps + 1, INF);
    previous[0] = 0;  // Starting positions consume no radio energy.

    for (int i = 0; i <= farmer_steps; ++i) {
        fill(current.begin(), current.end(), INF);

        for (int j = 0; j <= bessie_steps; ++j) {
            if (i == 0 && j == 0) {
                current[j] = 0;
                continue;
            }

            long long best_before_this_time = INF;

            // Farmer moves while Bessie waits: state (i-1,j) -> (i,j).
            if (i > 0) {
                best_before_this_time = min(best_before_this_time, previous[j]);
            }

            // Bessie moves while Farmer waits: state (i,j-1) -> (i,j).
            if (j > 0) {
                best_before_this_time = min(best_before_this_time, current[j - 1]);
            }

            // Both move: state (i-1,j-1) -> (i,j) in one time step.
            if (i > 0 && j > 0) {
                best_before_this_time = min(best_before_this_time, previous[j - 1]);
            }

            // Every non-start state represents the end of one time step, so
            // charge exactly once for the agents' new positions.
            current[j] = best_before_this_time
                + radio_cost(farmer_positions[i], bessie_positions[j]);
        }

        previous.swap(current);
    }

    cout << previous[bessie_steps] << '\n';
    return 0;
}
