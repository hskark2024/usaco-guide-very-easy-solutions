#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int length;
    cin >> length;
    vector<long long> first(length), second(length);
    for (long long &value : first) cin >> value;
    for (long long &value : second) cin >> value;

    // Give distinct values their rank in first-occurrence order in A.
    // Therefore every A prefix has a distinct-value set exactly {1, ..., k},
    // where k is its number of distinct values.
    unordered_map<long long, int> rank_in_first;
    rank_in_first.reserve(length * 2);
    vector<int> first_distinct_count(length + 1);
    int next_rank = 0;
    for (int i = 0; i < length; ++i) {
        if (!rank_in_first.count(first[i])) {
            rank_in_first[first[i]] = ++next_rank;
        }
        first_distinct_count[i + 1] = next_rank;
    }

    // For each B prefix remember whether all values exist in A, the number of
    // distinct ranks seen, and the maximum rank.  If count == maximum, those
    // ranks must be the complete consecutive set {1, ..., maximum}.
    vector<int> second_set_id(length + 1, -1);
    unordered_set<long long> seen_in_second;
    seen_in_second.reserve(length * 2);
    int distinct_count = 0;
    int maximum_rank = 0;
    bool contains_unknown_value = false;

    for (int i = 0; i < length; ++i) {
        if (seen_in_second.insert(second[i]).second) {
            ++distinct_count;
            auto rank_iterator = rank_in_first.find(second[i]);
            if (rank_iterator == rank_in_first.end()) {
                contains_unknown_value = true;
            } else {
                maximum_rank = max(maximum_rank, rank_iterator->second);
            }
        }

        if (!contains_unknown_value && distinct_count == maximum_rank) {
            second_set_id[i + 1] = maximum_rank;
        }
    }

    int query_count;
    cin >> query_count;
    while (query_count--) {
        int first_prefix, second_prefix;
        cin >> first_prefix >> second_prefix;

        // Equal integer IDs now mean equal mathematical sets.  No random
        // numbers or collision assumptions are needed.
        cout << (first_distinct_count[first_prefix] == second_set_id[second_prefix]
                     ? "Yes\n"
                     : "No\n");
    }
    return 0;
}
