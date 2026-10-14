#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int height, width, year_count;
    cin >> height >> width >> year_count;

    const int cell_count = height * width;
    vector<int> elevation(cell_count);
    for (int &value : elevation) cin >> value;

    // bucket[year] contains cells whose earliest possible sinking year is
    // exactly `year`. A cell is appended only once, so the total work across
    // every bucket stays linear in the grid size.
    vector<vector<int>> bucket(year_count + 1);
    vector<char> scheduled(cell_count, false);

    auto schedule = [&](int cell, int first_sea_year) {
        if (scheduled[cell]) return;
        scheduled[cell] = true;

        // The cell needs both conditions: it must already touch the sea, and
        // the sea level must reach its elevation. The later event wins.
        const int sink_year = max(first_sea_year, elevation[cell]);
        if (sink_year <= year_count) bucket[sink_year].push_back(cell);
    };

    // Boundary cells touch the surrounding sea at year 0. Corners are passed
    // more than once, but `scheduled` makes this harmless.
    for (int row = 0; row < height; ++row) {
        schedule(row * width, 0);
        schedule(row * width + width - 1, 0);
    }
    for (int column = 0; column < width; ++column) {
        schedule(column, 0);
        schedule((height - 1) * width + column, 0);
    }

    const int row_change[4] = {1, -1, 0, 0};
    const int column_change[4] = {0, 0, 1, -1};
    int remaining_area = cell_count;

    for (int year = 1; year <= year_count; ++year) {
        // New cells may be appended to this same bucket while we process it.
        // An index-based loop deliberately includes that chain reaction.
        for (size_t cursor = 0; cursor < bucket[year].size(); ++cursor) {
            const int cell = bucket[year][cursor];
            const int row = cell / width;
            const int column = cell % width;
            --remaining_area;

            for (int direction = 0; direction < 4; ++direction) {
                const int next_row = row + row_change[direction];
                const int next_column = column + column_change[direction];
                if (next_row < 0 || next_row >= height ||
                    next_column < 0 || next_column >= width) {
                    continue;
                }

                // This neighbor becomes sea-adjacent now. It sinks now if its
                // elevation is already low enough, or waits for its own
                // elevation year otherwise.
                schedule(next_row * width + next_column, year);
            }
        }

        cout << remaining_area << '\n';
    }
}
