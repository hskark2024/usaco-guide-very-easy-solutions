#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int cell_count;
    cin >> cell_count;

    vector<int> color(cell_count);
    for (int &value : color) {
        cin >> value;
    }

    // strokes[left][right] is the minimum number of interval brush strokes
    // needed to create the inclusive final segment color[left..right].
    vector<vector<int>> strokes(
        cell_count,
        vector<int>(cell_count, 0)
    );

    // Length-one intervals need one stroke.  Longer answers depend only on
    // shorter intervals, so fill the table by increasing interval length.
    for (int index = 0; index < cell_count; ++index) {
        strokes[index][index] = 1;
    }

    for (int length = 2; length <= cell_count; ++length) {
        for (int left = 0; left + length <= cell_count; ++left) {
            const int right = left + length - 1;

            // Baseline: finish cell `left` with its own stroke, independently
            // of an optimal painting of everything to its right.
            strokes[left][right] = 1 + strokes[left + 1][right];

            // When another cell has the same final color, one stroke can be
            // responsible for both endpoints.  Paint the middle independently,
            // then reuse the stroke already counted by strokes[match][right].
            for (int match = left + 1; match <= right; ++match) {
                if (color[left] != color[match]) {
                    continue;
                }

                // The interval between adjacent matching positions is empty
                // and costs zero; otherwise its answer is already available.
                const int middle_cost =
                    (match == left + 1) ? 0 : strokes[left + 1][match - 1];
                strokes[left][right] = min(
                    strokes[left][right],
                    middle_cost + strokes[match][right]
                );
            }
        }
    }

    cout << strokes[0][cell_count - 1] << '\n';
    return 0;
}
