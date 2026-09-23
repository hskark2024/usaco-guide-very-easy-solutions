#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // The original USACO judge reads nocross.in and writes nocross.out.
    // Keeping stdin/stdout as a fallback makes the same program convenient
    // for repository smoke tests and ordinary terminal use.
    if (FILE *input_file = fopen("nocross.in", "r")) {
        fclose(input_file);
        freopen("nocross.in", "r", stdin);
        freopen("nocross.out", "w", stdout);
    }

    int field_count;
    cin >> field_count;

    vector<int> upper(field_count);
    vector<int> lower(field_count);
    for (int &breed : upper) cin >> breed;
    for (int &breed : lower) cin >> breed;

    // Imagine a grid whose rows are prefixes of the upper ordering and whose
    // columns are prefixes of the lower ordering.  A noncrossing crosswalk
    // consumes one field from both sides, exactly like a tolerant version of
    // longest common subsequence: the two breed IDs need not be equal, only
    // within four of one another.
    vector<int> previous(field_count + 1, 0);
    vector<int> current(field_count + 1, 0);

    for (int upper_prefix = 1; upper_prefix <= field_count; ++upper_prefix) {
        // With zero lower fields, no crosswalk can be drawn.
        current[0] = 0;

        for (int lower_prefix = 1; lower_prefix <= field_count; ++lower_prefix) {
            // We may leave the newest upper field unmatched, or leave the
            // newest lower field unmatched.  These two choices also preserve
            // every solution made from smaller prefixes.
            current[lower_prefix] = max(
                previous[lower_prefix],
                current[lower_prefix - 1]
            );

            // Connecting the two newest fields can only follow a solution
            // that used neither endpoint.  Because every earlier connection
            // lies completely inside the smaller prefixes, the new crosswalk
            // cannot intersect any of them.
            if (abs(upper[upper_prefix - 1] - lower[lower_prefix - 1]) <= 4) {
                current[lower_prefix] = max(
                    current[lower_prefix],
                    previous[lower_prefix - 1] + 1
                );
            }
        }

        // Only the immediately preceding row is needed by the next row.
        previous.swap(current);
    }

    cout << previous[field_count] << '\n';
    return 0;
}
