#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string first, second;
    cin >> first >> second;

    // Make the second string the shorter dimension. The recurrence is
    // symmetric, and this choice reduces memory to O(min(n, m)).
    if (second.size() > first.size()) swap(first, second);

    // previous[j] is the edit distance between the already processed prefix
    // of first and the first j letters of second. With an empty first prefix,
    // j insertions are necessary, giving the base row 0,1,2,...,m.
    vector<int> previous(second.size() + 1);
    vector<int> current(second.size() + 1);
    iota(previous.begin(), previous.end(), 0);

    for (size_t i = 1; i <= first.size(); ++i) {
        // Turning i letters into an empty string requires i deletions.
        current[0] = static_cast<int>(i);

        for (size_t j = 1; j <= second.size(); ++j) {
            if (first[i - 1] == second[j - 1]) {
                // Matching final letters cost nothing: inherit the diagonal
                // subproblem after removing that equal letter from both.
                current[j] = previous[j - 1];
            } else {
                // The final operation is exactly one of:
                //   delete from first  -> previous[j]
                //   insert into first  -> current[j - 1]
                //   replace a letter  -> previous[j - 1]
                // Choose the cheapest predecessor and pay for one operation.
                current[j] = 1 + min({previous[j], current[j - 1],
                                      previous[j - 1]});
            }
        }

        previous.swap(current);
    }

    cout << previous[second.size()] << '\n';
    return 0;
}
