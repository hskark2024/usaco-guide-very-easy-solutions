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

    // USACO's judge reads time.in/time.out.  Standard input/output remains
    // available when the input file is absent, which is useful for local tests.
    if (FILE *input_file = fopen("time.in", "r")) {
        fclose(input_file);
        freopen("time.in", "r", stdin);
        freopen("time.out", "w", stdout);
    }

    int city_count, road_count;
    long long cost_coefficient;
    cin >> city_count >> road_count >> cost_coefficient;

    vector<long long> reward(city_count);
    for (long long &value : reward) {
        cin >> value;
    }

    // Store directed roads as edge pairs.  On each simulated day, every road
    // transfers the best reachable earnings from its start to its destination.
    vector<pair<int, int>> roads;
    roads.reserve(road_count);
    for (int road = 0; road < road_count; ++road) {
        int from, to;
        cin >> from >> to;
        roads.push_back({from - 1, to - 1});
    }

    const long long UNREACHABLE = numeric_limits<long long>::min() / 4;

    // previous[city] is the greatest gross reward obtainable after exactly the
    // current number of days while finishing in that city.  The journey starts
    // at city 0 on day 0 and has earned nothing yet.
    vector<long long> previous(city_count, UNREACHABLE);
    previous[0] = 0;

    // Visiting no other city is allowed, so zero is always a valid net profit.
    long long answer = 0;

    // A trip of t days can collect at most 1000*t reward, while its cost is at
    // least t^2 because C >= 1.  For t > 1000 the net value is negative, so no
    // optimal positive-profit trip needs more than 1000 days.  Day 1000 is kept
    // as a harmless boundary check (its upper bound is exactly zero when C=1).
    constexpr int MAX_DAYS = 1000;
    for (int day = 1; day <= MAX_DAYS; ++day) {
        vector<long long> current(city_count, UNREACHABLE);

        for (const auto &[from, to] : roads) {
            // A route reaching 'from' yesterday can follow this road today.
            // Unreachable sources are skipped so the negative sentinel cannot
            // accidentally participate in arithmetic.
            if (previous[from] == UNREACHABLE) {
                continue;
            }

            const long long candidate = previous[from] + reward[to];
            current[to] = max(current[to], candidate);
        }

        // A trip is valid only when it has returned to city 1 (index 0).  The
        // DP stores gross reward, so subtract the quadratic travel cost here.
        if (current[0] != UNREACHABLE) {
            const long long travel_cost = cost_coefficient * day * day;
            answer = max(answer, current[0] - travel_cost);
        }

        // Advance the rolling DP layer.  Keeping only two days uses O(N) space.
        previous.swap(current);
    }

    cout << answer << '\n';
    return 0;
}
