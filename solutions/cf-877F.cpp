#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

// Codeforces 877F: Ann and Books
//
// Treat math problems as positive and economics problems as negative.  A
// subarray has signed sum K exactly when its two surrounding prefix sums
// satisfy prefix[right] - prefix[left] = K.
struct Query {
    int left_prefix;
    int right_prefix;
    int original_index;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int book_count;
    long long wanted_difference;
    cin >> book_count >> wanted_difference;

    vector<int> type(book_count + 1);
    for (int index = 1; index <= book_count; ++index) {
        cin >> type[index];
    }

    vector<long long> prefix(book_count + 1, 0);
    for (int index = 1; index <= book_count; ++index) {
        long long problems;
        cin >> problems;

        // Type 1 contributes math problems; type 2 contributes the negative
        // of its economics problems.
        const long long signed_value = type[index] == 1 ? problems : -problems;
        prefix[index] = prefix[index - 1] + signed_value;
    }

    int query_count;
    cin >> query_count;
    vector<Query> queries(query_count);
    for (int index = 0; index < query_count; ++index) {
        int left, right;
        cin >> left >> right;

        // Every nonempty subarray inside [left, right] corresponds to an
        // ordered pair of prefix indices in [left-1, right].
        queries[index] = {left - 1, right, index};
    }

    // Coordinate-compress the prefix values.  We also precompute where
    // prefix[i]-K and prefix[i]+K occur, so every Mo pointer move is O(1).
    vector<long long> compressed_values = prefix;
    sort(compressed_values.begin(), compressed_values.end());
    compressed_values.erase(
        unique(compressed_values.begin(), compressed_values.end()),
        compressed_values.end()
    );

    vector<int> value_id(book_count + 1);
    vector<int> minus_k_id(book_count + 1, -1);
    vector<int> plus_k_id(book_count + 1, -1);

    auto find_id = [&](long long value) -> int {
        const auto it = lower_bound(
            compressed_values.begin(), compressed_values.end(), value
        );
        if (it == compressed_values.end() || *it != value) return -1;
        return static_cast<int>(it - compressed_values.begin());
    };

    for (int index = 0; index <= book_count; ++index) {
        value_id[index] = find_id(prefix[index]);
        minus_k_id[index] = find_id(prefix[index] - wanted_difference);
        plus_k_id[index] = find_id(prefix[index] + wanted_difference);
    }

    const int block_size = max(
        1,
        static_cast<int>((book_count + 1) / max(1.0, sqrt(query_count)))
    );

    // Alternating the right-end order in neighboring blocks avoids many long
    // sweeps back to the beginning and improves the constant factor.
    sort(queries.begin(), queries.end(), [&](const Query &first, const Query &second) {
        const int first_block = first.left_prefix / block_size;
        const int second_block = second.left_prefix / block_size;
        if (first_block != second_block) return first_block < second_block;
        if (first_block % 2 == 0) {
            return first.right_prefix < second.right_prefix;
        }
        return first.right_prefix > second.right_prefix;
    });

    vector<int> frequency(compressed_values.size(), 0);
    vector<long long> answers(query_count);
    long long current_answer = 0;
    int current_left = 0;
    int current_right = -1;

    auto add_right = [&](int index) {
        // This new prefix is the larger index in every new pair.  We need an
        // earlier prefix whose value is prefix[index]-K.
        if (minus_k_id[index] != -1) {
            current_answer += frequency[minus_k_id[index]];
        }
        ++frequency[value_id[index]];
    };

    auto add_left = [&](int index) {
        // This new prefix is the smaller index.  Its partner must equal
        // prefix[index]+K so partner-prefix[index] is K.
        if (plus_k_id[index] != -1) {
            current_answer += frequency[plus_k_id[index]];
        }
        ++frequency[value_id[index]];
    };

    auto remove_right = [&](int index) {
        // Remove the value first so K=0 does not pair the prefix with itself.
        --frequency[value_id[index]];
        if (minus_k_id[index] != -1) {
            current_answer -= frequency[minus_k_id[index]];
        }
    };

    auto remove_left = [&](int index) {
        --frequency[value_id[index]];
        if (plus_k_id[index] != -1) {
            current_answer -= frequency[plus_k_id[index]];
        }
    };

    for (const Query &query : queries) {
        while (current_left > query.left_prefix) add_left(--current_left);
        while (current_right < query.right_prefix) add_right(++current_right);
        while (current_left < query.left_prefix) remove_left(current_left++);
        while (current_right > query.right_prefix) remove_right(current_right--);
        answers[query.original_index] = current_answer;
    }

    for (long long answer : answers) {
        cout << answer << '\n';
    }
    return 0;
}
