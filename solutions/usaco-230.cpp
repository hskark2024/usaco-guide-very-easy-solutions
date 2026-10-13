#include <algorithm>
#include <deque>
#include <iostream>
#include <limits>
#include <queue>
#include <string>
#include <utility>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int rows, columns;
    cin >> rows >> columns;
    vector<string> grid(rows);
    for (string &row : grid) cin >> row;

    constexpr int DR[4] = {1, 0, -1, 0};
    constexpr int DC[4] = {0, 1, 0, -1};
    const int infinity = numeric_limits<int>::max() / 4;

    // First turn every four-directionally connected group of X cells into one
    // numbered island.  Shallow and deep water never join two X components.
    vector<vector<int>> island_id(rows, vector<int>(columns, -1));
    int island_count = 0;
    for (int start_row = 0; start_row < rows; ++start_row) {
        for (int start_column = 0; start_column < columns; ++start_column) {
            if (grid[start_row][start_column] != 'X' ||
                island_id[start_row][start_column] != -1) {
                continue;
            }

            queue<pair<int, int>> cells;
            cells.push({start_row, start_column});
            island_id[start_row][start_column] = island_count;

            while (!cells.empty()) {
                const auto [row, column] = cells.front();
                cells.pop();

                for (int direction = 0; direction < 4; ++direction) {
                    const int next_row = row + DR[direction];
                    const int next_column = column + DC[direction];
                    if (next_row < 0 || next_row >= rows || next_column < 0 ||
                        next_column >= columns) {
                        continue;
                    }
                    if (grid[next_row][next_column] == 'X' &&
                        island_id[next_row][next_column] == -1) {
                        island_id[next_row][next_column] = island_count;
                        cells.push({next_row, next_column});
                    }
                }
            }
            ++island_count;
        }
    }

    // travel_cost[a][b] is the fewest shallow-water squares needed to get
    // from island a to island b.  Entering X costs 0, entering S costs 1, and
    // deep water is forbidden, so multi-source 0-1 BFS is exactly appropriate.
    vector<vector<int>> travel_cost(
        island_count, vector<int>(island_count, infinity));

    for (int source = 0; source < island_count; ++source) {
        vector<vector<int>> distance(rows, vector<int>(columns, infinity));
        deque<pair<int, int>> frontier;

        // Starting anywhere on the source island is free.  Seeding all of its
        // cells avoids charging for movement within a large island.
        for (int row = 0; row < rows; ++row) {
            for (int column = 0; column < columns; ++column) {
                if (island_id[row][column] == source) {
                    distance[row][column] = 0;
                    frontier.push_back({row, column});
                }
            }
        }

        while (!frontier.empty()) {
            const auto [row, column] = frontier.front();
            frontier.pop_front();

            for (int direction = 0; direction < 4; ++direction) {
                const int next_row = row + DR[direction];
                const int next_column = column + DC[direction];
                if (next_row < 0 || next_row >= rows || next_column < 0 ||
                    next_column >= columns ||
                    grid[next_row][next_column] == '.') {
                    continue;
                }

                const int step_cost = (grid[next_row][next_column] == 'S');
                const int candidate = distance[row][column] + step_cost;
                if (candidate >= distance[next_row][next_column]) continue;

                distance[next_row][next_column] = candidate;
                if (step_cost == 0) {
                    frontier.push_front({next_row, next_column});
                } else {
                    frontier.push_back({next_row, next_column});
                }
            }
        }

        // Any cell of the target island is an acceptable arrival point.
        for (int row = 0; row < rows; ++row) {
            for (int column = 0; column < columns; ++column) {
                const int target = island_id[row][column];
                if (target != -1) {
                    travel_cost[source][target] = min(
                        travel_cost[source][target], distance[row][column]);
                }
            }
        }
    }

    // visited_cost[mask][last] is the least swimming cost of a route that has
    // visited every island in mask and currently ends at `last`.
    const int all_masks = 1 << island_count;
    vector<vector<int>> visited_cost(
        all_masks, vector<int>(island_count, infinity));

    // The helicopter may land on any first island, so every single-island
    // state starts with zero swimming.
    for (int island = 0; island < island_count; ++island) {
        visited_cost[1 << island][island] = 0;
    }

    for (int mask = 1; mask < all_masks; ++mask) {
        for (int last = 0; last < island_count; ++last) {
            const int current = visited_cost[mask][last];
            if (current == infinity || !(mask & (1 << last))) continue;

            for (int next = 0; next < island_count; ++next) {
                if (mask & (1 << next)) continue;
                const int next_mask = mask | (1 << next);
                visited_cost[next_mask][next] = min(
                    visited_cost[next_mask][next],
                    current + travel_cost[last][next]);
            }
        }
    }

    cout << *min_element(visited_cost.back().begin(),
                         visited_cost.back().end())
         << '\n';
    return 0;
}
