#include <algorithm>
#include <iostream>
#include <limits>
#include <string>
#include <vector>
using namespace std;

// Build the KMP failure table for one pattern.  We use exact character
// matching instead of probabilistic hashes, so adversarial strings cannot
// create a false substring or overlap match.
vector<int> prefix_function(const string &pattern) {
    vector<int> pi(pattern.size());
    for (int i = 1; i < static_cast<int>(pattern.size()); ++i) {
        int matched = pi[i - 1];
        while (matched > 0 && pattern[i] != pattern[matched]) {
            matched = pi[matched - 1];
        }
        if (pattern[i] == pattern[matched]) ++matched;
        pi[i] = matched;
    }
    return pi;
}

bool contains(const string &text, const string &pattern) {
    if (pattern.size() > text.size()) return false;
    const vector<int> pi = prefix_function(pattern);
    int matched = 0;

    for (char character : text) {
        while (matched > 0 && character != pattern[matched]) {
            matched = pi[matched - 1];
        }
        if (character == pattern[matched]) ++matched;
        if (matched == static_cast<int>(pattern.size())) return true;
    }
    return false;
}

// Find the greatest k for which the last k characters of left equal the first
// k characters of right.  Running KMP for right while scanning left leaves the
// automaton state equal to precisely that suffix/prefix overlap.
int overlap_length(const string &left, const string &right) {
    const vector<int> pi = prefix_function(right);
    int matched = 0;

    for (int index = 0; index < static_cast<int>(left.size()); ++index) {
        const char character = left[index];
        while (matched > 0 && character != right[matched]) {
            matched = pi[matched - 1];
        }
        if (character == right[matched]) ++matched;

        if (matched == static_cast<int>(right.size())) {
            // A full match ending at the last character is the best possible
            // overlap.  Otherwise fall back so scanning can continue safely.
            if (index + 1 == static_cast<int>(left.size())) return matched;
            matched = pi[matched - 1];
        }
    }
    return matched;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int input_count;
    cin >> input_count;
    vector<string> input(input_count);
    for (string &phrase : input) cin >> phrase;

    // A phrase contained in another phrase needs no separate placement.  For
    // equal duplicates, keep only the first copy so at least one survives.
    vector<bool> redundant(input_count, false);
    for (int i = 0; i < input_count; ++i) {
        for (int j = 0; j < input_count; ++j) {
            if (i == j) continue;
            const bool strictly_longer = input[j].size() > input[i].size();
            const bool earlier_duplicate = input[j].size() == input[i].size() && j < i;
            if ((strictly_longer || earlier_duplicate) && contains(input[j], input[i])) {
                redundant[i] = true;
                break;
            }
        }
    }

    vector<string> phrases;
    for (int i = 0; i < input_count; ++i) {
        if (!redundant[i]) phrases.push_back(input[i]);
    }

    const int count = phrases.size();
    vector<vector<int>> overlap(count, vector<int>(count));
    for (int i = 0; i < count; ++i) {
        for (int j = 0; j < count; ++j) {
            if (i != j) overlap[i][j] = overlap_length(phrases[i], phrases[j]);
        }
    }

    // dp[mask][last] is the shortest superstring length that uses exactly the
    // phrases in mask and ends with phrase last.  We need only the length, not
    // the actual superstring.
    const int full_mask = (1 << count) - 1;
    const int infinity = numeric_limits<int>::max() / 4;
    vector<vector<int>> dp(1 << count, vector<int>(count, infinity));
    for (int i = 0; i < count; ++i) {
        dp[1 << i][i] = phrases[i].size();
    }

    for (int mask = 1; mask <= full_mask; ++mask) {
        for (int last = 0; last < count; ++last) {
            if (dp[mask][last] == infinity) continue;

            for (int next = 0; next < count; ++next) {
                if (mask & (1 << next)) continue;
                const int next_mask = mask | (1 << next);
                const int added = phrases[next].size() - overlap[last][next];
                dp[next_mask][next] = min(
                    dp[next_mask][next], dp[mask][last] + added);
            }
        }
    }

    cout << *min_element(dp[full_mask].begin(), dp[full_mask].end()) << '\n';
    return 0;
}
