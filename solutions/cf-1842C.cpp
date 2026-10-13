#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int test_count;
    cin >> test_count;
    while (test_count--) {
        int ball_count;
        cin >> ball_count;

        vector<int> color(ball_count + 1);
        for (int index = 1; index <= ball_count; ++index) cin >> color[index];

        const int infinity = numeric_limits<int>::max() / 4;

        // kept[i] is the minimum number of balls that must remain after all
        // chosen deletions lie inside the original prefix [1..i].  Thinking in
        // terms of kept balls makes a whole deleted interval cost zero.
        vector<int> kept(ball_count + 1, infinity);
        kept[0] = 0;

        // best_before[c] is min(kept[left-1]) over earlier positions `left`
        // whose ball has color c.  Such a left endpoint can pair with the
        // current equal-colored ball and delete the full interval [left..i].
        vector<int> best_before(ball_count + 1, infinity);

        for (int index = 1; index <= ball_count; ++index) {
            const int current_color = color[index];

            // Option 1: do not use this ball as the right end of a deletion,
            // so it remains after the best plan for the previous prefix.
            const int keep_current = kept[index - 1] + 1;

            // Option 2: match an earlier equal color.  Everything from that
            // earlier endpoint through this index disappears, leaving exactly
            // the optimum prefix that ended just before the chosen endpoint.
            const int delete_interval = best_before[current_color];
            kept[index] = min(keep_current, delete_interval);

            // Make this index available as the left endpoint of a later
            // deletion.  Update after computing kept[index], because an
            // operation requires two different positions.
            best_before[current_color] =
                min(best_before[current_color], kept[index - 1]);
        }

        // Maximizing removed balls is the same as minimizing survivors.
        cout << ball_count - kept[ball_count] << '\n';
    }
    return 0;
}
