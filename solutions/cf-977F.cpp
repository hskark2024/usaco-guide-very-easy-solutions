#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int value_count;
    cin >> value_count;

    vector<int> values(value_count);
    vector<int> previous_index(value_count, -1);

    // For each ending value x, remember the best consecutive subsequence
    // ending at x and the array position of its final element.  We do not
    // need a full O(N^2) LIS table because the only allowed predecessor of x
    // is exactly x - 1.
    unordered_map<int, int> best_length_by_value;
    unordered_map<int, int> last_index_by_value;
    best_length_by_value.reserve(value_count * 2);
    last_index_by_value.reserve(value_count * 2);

    int overall_best_length = 0;
    int overall_last_index = -1;

    for (int index = 0; index < value_count; ++index) {
        cin >> values[index];
        const int value = values[index];

        // Any valid chain ending here must append this value to a chain that
        // ended at value - 1 earlier in the array.  If no such chain exists,
        // this element starts a new length-one chain.
        int candidate_length = 1;
        int candidate_previous_index = -1;
        const auto predecessor = best_length_by_value.find(value - 1);
        if (predecessor != best_length_by_value.end()) {
            candidate_length = predecessor->second + 1;
            candidate_previous_index = last_index_by_value[value - 1];
        }

        // Keep a parent pointer so the chosen values can later be recovered
        // as original one-based indices, as required by the judge.
        previous_index[index] = candidate_previous_index;

        const auto existing = best_length_by_value.find(value);
        if (existing == best_length_by_value.end()
            || candidate_length > existing->second) {
            best_length_by_value[value] = candidate_length;
            last_index_by_value[value] = index;

            if (candidate_length > overall_best_length) {
                overall_best_length = candidate_length;
                overall_last_index = index;
            }
        }
    }

    // Follow parent pointers backward, then reverse to restore array order.
    vector<int> chosen_indices;
    for (int index = overall_last_index; index != -1;
         index = previous_index[index]) {
        chosen_indices.push_back(index + 1);
    }
    reverse(chosen_indices.begin(), chosen_indices.end());

    cout << overall_best_length << '\n';
    for (int position = 0; position < overall_best_length; ++position) {
        if (position != 0) {
            cout << ' ';
        }
        cout << chosen_indices[position];
    }
    cout << '\n';
    return 0;
}
