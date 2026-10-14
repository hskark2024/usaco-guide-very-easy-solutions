#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

struct Robot {
    int position;
    int input_index;
    char direction;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int test_count;
    cin >> test_count;
    while (test_count--) {
        int robot_count, wall;
        cin >> robot_count >> wall;

        vector<Robot> robots(robot_count);
        for (int index = 0; index < robot_count; ++index) {
            cin >> robots[index].position;
            robots[index].input_index = index;
        }
        for (Robot &robot : robots) cin >> robot.direction;

        // Spatial order, rather than input order, determines which robots can
        // meet first.
        sort(robots.begin(), robots.end(), [](const Robot &left, const Robot &right) {
            return left.position < right.position;
        });

        vector<int> answer(robot_count, -1);

        // A collision at an integer coordinate requires the starting
        // coordinates to have the same parity. Even and odd robots can
        // therefore be solved as two independent one-dimensional problems.
        for (int parity = 0; parity < 2; ++parity) {
            vector<int> unmatched_left;
            vector<int> unmatched_right;

            for (int index = 0; index < robot_count; ++index) {
                if (robots[index].position % 2 != parity) continue;

                if (robots[index].direction == 'R') {
                    // Save this robot until the nearest future left-moving
                    // robot arrives. LIFO pairing gives adjacent R-L pairs.
                    unmatched_right.push_back(index);
                } else if (!unmatched_right.empty()) {
                    // These robots move directly toward one another before
                    // either needs a wall reflection.
                    const int other = unmatched_right.back();
                    unmatched_right.pop_back();
                    const int time =
                        (robots[index].position - robots[other].position) / 2;
                    answer[robots[index].input_index] = time;
                    answer[robots[other].input_index] = time;
                } else {
                    // No right-moving robot lies before this one. It must use
                    // the left wall before it can meet anybody.
                    unmatched_left.push_back(index);
                }
            }

            // Remaining left-movers all appear before remaining right-movers.
            // Pair left-movers from the wall outward. After reflecting at 0,
            // a pair starting at x1 < x2 meets at time (x1 + x2) / 2.
            size_t left_used = 0;
            while (left_used + 1 < unmatched_left.size()) {
                const int first = unmatched_left[left_used];
                const int second = unmatched_left[left_used + 1];
                const int time =
                    (robots[first].position + robots[second].position) / 2;
                answer[robots[first].input_index] = time;
                answer[robots[second].input_index] = time;
                left_used += 2;
            }

            // Symmetrically, pair right-movers from the right wall inward.
            // The two travel (wall-x1) + (wall-x2) total distance.
            int right_used = static_cast<int>(unmatched_right.size()) - 1;
            while (right_used - 1 >= 0) {
                const int first = unmatched_right[right_used];
                const int second = unmatched_right[right_used - 1];
                const int time =
                    (2 * wall - robots[first].position - robots[second].position) / 2;
                answer[robots[first].input_index] = time;
                answer[robots[second].input_index] = time;
                right_used -= 2;
            }

            // If both lists have one robot left, the left one bounces off 0
            // and the right one bounces off `wall`. Unfolding both reflections
            // gives the distance formula below. If only one robot remains,
            // no same-parity partner exists, so its answer stays -1.
            if (left_used < unmatched_left.size() && right_used == 0) {
                const int left_robot = unmatched_left[left_used];
                const int right_robot = unmatched_right[0];
                const int time =
                    (2 * wall + robots[left_robot].position -
                     robots[right_robot].position) /
                    2;
                answer[robots[left_robot].input_index] = time;
                answer[robots[right_robot].input_index] = time;
            }
        }

        for (int index = 0; index < robot_count; ++index) {
            if (index) cout << ' ';
            cout << answer[index];
        }
        cout << '\n';
    }
}
