#include <algorithm>
#include <cstdio>
#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Support both USACO's historical file interface and stdin-based tests.
    if (FILE *input_file = fopen("movie.in", "r")) {
        fclose(input_file);
        freopen("movie.in", "r", stdin);
        freopen("movie.out", "w", stdout);
    }

    int movie_count;
    int target_time;
    cin >> movie_count >> target_time;

    vector<int> duration(movie_count);
    vector<vector<int>> showtimes(movie_count);
    for (int movie = 0; movie < movie_count; ++movie) {
        int showing_count;
        cin >> duration[movie] >> showing_count;
        showtimes[movie].resize(showing_count);
        for (int &start_time : showtimes[movie]) {
            cin >> start_time;
        }
    }

    const int state_count = 1 << movie_count;

    // covered_until[mask] is the latest time through which Bessie can watch
    // continuously, starting at time zero, after using exactly mask's movies.
    // The value -1 marks an unreachable subset.
    vector<int> covered_until(state_count, -1);
    covered_until[0] = 0;

    int minimum_movies = movie_count + 1;

    for (int mask = 0; mask < state_count; ++mask) {
        const int current_time = covered_until[mask];
        if (current_time < 0) {
            continue;
        }

        if (current_time >= target_time) {
            minimum_movies = min(minimum_movies, __builtin_popcount(mask));
            // Adding more movies can never improve this state's movie count.
            continue;
        }

        for (int movie = 0; movie < movie_count; ++movie) {
            const int movie_bit = 1 << movie;
            if ((mask & movie_bit) != 0) {
                continue;
            }

            // To avoid a gap, the showing must have started no later than the
            // current covered time.  The latest such showing always ends at
            // least as late as every earlier showing of this same movie.
            const auto first_late_showing = upper_bound(
                showtimes[movie].begin(),
                showtimes[movie].end(),
                current_time
            );
            if (first_late_showing == showtimes[movie].begin()) {
                continue;
            }

            const int start_time = *prev(first_late_showing);
            const int finish_time = start_time + duration[movie];

            // A showing that has already ended cannot extend continuous
            // coverage.  Equality is harmless but creates no improvement.
            if (finish_time <= current_time) {
                continue;
            }

            const int next_mask = mask | movie_bit;
            covered_until[next_mask] = max(
                covered_until[next_mask],
                finish_time
            );
        }
    }

    if (minimum_movies == movie_count + 1) {
        cout << -1 << '\n';
    } else {
        cout << minimum_movies << '\n';
    }
    return 0;
}
