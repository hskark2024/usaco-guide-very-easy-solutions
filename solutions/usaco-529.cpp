#include <algorithm>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

using int64 = long long;

// Censoring is naturally processed with an output stack.  Only the suffix can
// become a new occurrence when one character is appended, so we never need to
// rescan the already-safe prefix.
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string source, forbidden;
    cin >> source >> forbidden;

    constexpr int64 MOD_1 = 1'000'000'007LL;
    constexpr int64 MOD_2 = 1'000'000'009LL;
    constexpr int64 BASE = 911'382'323LL;

    const int pattern_length = static_cast<int>(forbidden.size());

    // Compute the hash of the forbidden word once.  A second modulus makes a
    // false candidate vanishingly unlikely; an exact comparison below makes
    // even a hash collision harmless.
    int64 forbidden_hash_1 = 0;
    int64 forbidden_hash_2 = 0;
    for (char letter : forbidden) {
        const int value = letter - 'a' + 1;
        forbidden_hash_1 = (forbidden_hash_1 * BASE + value) % MOD_1;
        forbidden_hash_2 = (forbidden_hash_2 * BASE + value) % MOD_2;
    }

    vector<int64> power_1(source.size() + 1, 1);
    vector<int64> power_2(source.size() + 1, 1);
    for (size_t length = 1; length <= source.size(); ++length) {
        power_1[length] = power_1[length - 1] * BASE % MOD_1;
        power_2[length] = power_2[length - 1] * BASE % MOD_2;
    }

    string result;
    result.reserve(source.size());

    // prefix_hash[k] is the hash of the first k characters currently in the
    // result stack.  Resizing these vectors therefore rolls a deletion back in
    // O(1), exactly like popping characters from the string.
    vector<int64> prefix_1(1, 0);
    vector<int64> prefix_2(1, 0);
    prefix_1.reserve(source.size() + 1);
    prefix_2.reserve(source.size() + 1);

    for (char letter : source) {
        const int value = letter - 'a' + 1;
        result.push_back(letter);
        prefix_1.push_back((prefix_1.back() * BASE + value) % MOD_1);
        prefix_2.push_back((prefix_2.back() * BASE + value) % MOD_2);

        if (static_cast<int>(result.size()) < pattern_length) {
            continue;
        }

        const int end = static_cast<int>(result.size());
        const int start = end - pattern_length;
        const int64 suffix_hash_1 =
            (prefix_1[end]
             - prefix_1[start] * power_1[pattern_length] % MOD_1
             + MOD_1)
            % MOD_1;
        const int64 suffix_hash_2 =
            (prefix_2[end]
             - prefix_2[start] * power_2[pattern_length] % MOD_2
             + MOD_2)
            % MOD_2;

        if (suffix_hash_1 == forbidden_hash_1
            && suffix_hash_2 == forbidden_hash_2
            && equal(result.begin() + start, result.end(), forbidden.begin())) {
            // The newly formed suffix is forbidden.  Removing it may reveal a
            // boundary match later, and the future appends will detect it.
            result.resize(start);
            prefix_1.resize(start + 1);
            prefix_2.resize(start + 1);
        }
    }

    cout << result << '\n';
    return 0;
}
