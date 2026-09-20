#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// LeetCode calls this method directly.  Keeping the algorithm in a class makes
// the core easy to paste into the judge, while main below supplies a tiny
// whitespace-delimited adapter for this repository's compiler and test tools.
class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        // The rolling row is indexed by the shorter string.  This is not
        // required for the official limits, but it gives the best O(min(n,m))
        // memory bound at no cost to readability.
        if (text1.size() < text2.size()) {
            swap(text1, text2);
        }

        // previous[j] is the LCS length for the already processed prefix of
        // text1 and the first j characters of text2.  current builds the same
        // values after adding one more character from text1.
        vector<int> previous(text2.size() + 1, 0);
        vector<int> current(text2.size() + 1, 0);

        for (char first_character : text1) {
            // An empty second prefix has no nonempty common subsequence.
            current[0] = 0;

            for (size_t j = 1; j <= text2.size(); ++j) {
                if (first_character == text2[j - 1]) {
                    // Match these two final characters.  Any subsequence before
                    // them must belong to the two prefixes that omit both.
                    current[j] = previous[j - 1] + 1;
                } else {
                    // The two final characters differ, so at least one is not
                    // used by an optimal answer.  Try dropping either one.
                    current[j] = max(previous[j], current[j - 1]);
                }
            }

            // The completed row becomes the source for the next character.
            previous.swap(current);
        }

        return previous[text2.size()];
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string text1, text2;
    cin >> text1 >> text2;

    Solution solution;
    cout << solution.longestCommonSubsequence(text1, text2) << '\n';
    return 0;
}
