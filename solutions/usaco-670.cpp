#include <algorithm>
#include <cstdio>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

struct Point {
    int x;
    int y;
};

long long squared_distance(const Point &first, const Point &second) {
    // Cast before multiplying so a future coordinate-range change cannot make
    // the intermediate product overflow a 32-bit int.
    const long long dx = first.x - second.x;
    const long long dy = first.y - second.y;
    return dx * dx + dy * dy;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // The official judge uses checklist.in/checklist.out.  Falling back to
    // stdin/stdout keeps the exact same program convenient for local tests.
    if (FILE *input_file = fopen("checklist.in", "r")) {
        fclose(input_file);
        freopen("checklist.in", "r", stdin);
        freopen("checklist.out", "w", stdout);
    }

    int holstein_count, guernsey_count;
    cin >> holstein_count >> guernsey_count;

    // One-based indexing makes state (i,j) read naturally as "the first i
    // Holsteins and first j Guernseys have been visited."
    vector<Point> holsteins(holstein_count + 1);
    vector<Point> guernseys(guernsey_count + 1);
    for (int i = 1; i <= holstein_count; ++i) {
        cin >> holsteins[i].x >> holsteins[i].y;
    }
    for (int j = 1; j <= guernsey_count; ++j) {
        cin >> guernseys[j].x >> guernseys[j].y;
    }

    // When H1 is also HH, the only possible ordered tour visits all
    // Guernseys and returns to that same required endpoint.  Handling this
    // boundary directly avoids needing a special "revisit HH" DP transition.
    if (holstein_count == 1) {
        long long answer = squared_distance(holsteins[1], guernseys[1]);
        for (int j = 1; j < guernsey_count; ++j) {
            answer += squared_distance(guernseys[j], guernseys[j + 1]);
        }
        answer += squared_distance(guernseys[guernsey_count], holsteins[1]);
        cout << answer << '\n';
        return 0;
    }

    const long long INF = numeric_limits<long long>::max() / 4;

    // end_at_h[i][j] is the least energy after visiting H1..Hi and G1..Gj,
    // with the tour currently at Hi.  end_at_g stores the analogous state at
    // Gj.  Two endpoint types are necessary because the next travel cost
    // depends on the exact current cow, not only on how many cows were seen.
    vector<vector<long long>> end_at_h(
        holstein_count + 1,
        vector<long long>(guernsey_count + 1, INF)
    );
    vector<vector<long long>> end_at_g(
        holstein_count + 1,
        vector<long long>(guernsey_count + 1, INF)
    );

    // The walk is already at H1 before spending any energy.  No state may
    // begin at a Guernsey or skip this required first Holstein.
    end_at_h[1][0] = 0;

    for (int i = 1; i <= holstein_count; ++i) {
        for (int j = 0; j <= guernsey_count; ++j) {
            if (end_at_h[i][j] != INF) {
                if (i < holstein_count) {
                    // Visit the next Holstein, preserving both breed orders.
                    end_at_h[i + 1][j] = min(
                        end_at_h[i + 1][j],
                        end_at_h[i][j]
                            + squared_distance(holsteins[i], holsteins[i + 1])
                    );
                }
                if (j < guernsey_count) {
                    // Switch breeds and visit the next unseen Guernsey.
                    end_at_g[i][j + 1] = min(
                        end_at_g[i][j + 1],
                        end_at_h[i][j]
                            + squared_distance(holsteins[i], guernseys[j + 1])
                    );
                }
            }

            // A G-ending state exists only after at least one Guernsey.  The
            // guard also avoids reading the unused guernseys[0] sentinel.
            if (j > 0 && end_at_g[i][j] != INF) {
                if (i < holstein_count) {
                    end_at_h[i + 1][j] = min(
                        end_at_h[i + 1][j],
                        end_at_g[i][j]
                            + squared_distance(guernseys[j], holsteins[i + 1])
                    );
                }
                if (j < guernsey_count) {
                    end_at_g[i][j + 1] = min(
                        end_at_g[i][j + 1],
                        end_at_g[i][j]
                            + squared_distance(guernseys[j], guernseys[j + 1])
                    );
                }
            }
        }
    }

    // The required final location is HH, so the G-ending state is deliberately
    // not considered even if it has smaller energy.
    cout << end_at_h[holstein_count][guernsey_count] << '\n';
    return 0;
}
