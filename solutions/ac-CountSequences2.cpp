#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int test_count, modulus;
    cin >> test_count >> modulus;

    // Read every case first. The largest total frequency tells us exactly how
    // many rows of Pascal's triangle this input needs.
    vector<vector<int>> cases(test_count);
    int maximum_length = 0;
    for (auto &counts : cases) {
        int value_count;
        cin >> value_count;
        counts.resize(value_count);

        int total = 0;
        for (int &count : counts) {
            cin >> count;
            total += count;
        }
        maximum_length = max(maximum_length, total);
    }

    // Store only the lower triangle in one flat array. Row n begins at
    // n * (n + 1) / 2 and contains C(n, 0) through C(n, n).
    const auto offset = [](int row) -> size_t {
        return static_cast<size_t>(row) * (row + 1) / 2;
    };
    vector<int> choose(offset(maximum_length + 1));
    choose[0] = 1 % modulus;

    // Pascal addition uses no division, so it is valid even when the modulus
    // is composite and modular inverses do not exist.
    for (int n = 1; n <= maximum_length; ++n) {
        const size_t current = offset(n);
        const size_t previous = offset(n - 1);
        choose[current] = 1 % modulus;
        choose[current + n] = 1 % modulus;
        for (int k = 1; k < n; ++k) {
            choose[current + k] =
                (choose[previous + k - 1] + choose[previous + k]) % modulus;
        }
    }

    for (const auto &counts : cases) {
        long long answer = 1 % modulus;
        int placed = 0;

        // After 'placed' symbols are arranged, insert count identical copies
        // of the next value into the enlarged sequence. There are
        // C(placed + count, count) choices for their positions.
        for (int count : counts) {
            placed += count;
            answer = answer * choose[offset(placed) + count] % modulus;
        }
        cout << answer << '\n';
    }

    return 0;
}
