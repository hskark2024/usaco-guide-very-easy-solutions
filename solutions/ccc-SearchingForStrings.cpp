#include <array>
#include <cstdint>
#include <iostream>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;

// Two independent prime moduli make an accidental collision extraordinarily
// unlikely.  Each substring hash is normalized because get_hash removes the
// prefix and its matching power of BASE.
class DoubleRollingHash {
private:
    static constexpr int64_t MOD_1 = 1'000'000'007LL;
    static constexpr int64_t MOD_2 = 1'000'000'009LL;
    static constexpr int64_t BASE = 911'382'323LL;

    vector<int64_t> power_1, power_2;
    vector<int64_t> prefix_1, prefix_2;

public:
    explicit DoubleRollingHash(const string &text) {
        const int length = static_cast<int>(text.size());
        power_1.assign(length + 1, 1);
        power_2.assign(length + 1, 1);
        prefix_1.assign(length + 1, 0);
        prefix_2.assign(length + 1, 0);

        for (int index = 0; index < length; ++index) {
            power_1[index + 1] = power_1[index] * BASE % MOD_1;
            power_2[index + 1] = power_2[index] * BASE % MOD_2;

            // Map a..z to 1..26.  Avoiding zero keeps leading letters visible.
            const int value = text[index] - 'a' + 1;
            prefix_1[index + 1] =
                (prefix_1[index] * BASE + value) % MOD_1;
            prefix_2[index + 1] =
                (prefix_2[index] * BASE + value) % MOD_2;
        }
    }

    pair<int64_t, int64_t> get_hash(int left, int right) const {
        // Return the hash of the half-open interval [left, right).
        int64_t hash_1 =
            (prefix_1[right]
             - prefix_1[left] * power_1[right - left] % MOD_1
             + MOD_1)
            % MOD_1;
        int64_t hash_2 =
            (prefix_2[right]
             - prefix_2[left] * power_2[right - left] % MOD_2
             + MOD_2)
            % MOD_2;
        return {hash_1, hash_2};
    }
};

static uint64_t pack_hash(pair<int64_t, int64_t> hash_value) {
    // Both residues fit in 32 bits, so this is a one-to-one packing of the
    // pair.  unordered_set can then store one ordinary integer per substring.
    return (static_cast<uint64_t>(hash_value.first) << 32)
           | static_cast<uint32_t>(hash_value.second);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string needle, haystack;
    cin >> needle >> haystack;

    const int window_length = static_cast<int>(needle.size());
    const int text_length = static_cast<int>(haystack.size());
    if (window_length > text_length) {
        // No substring can be long enough to be a permutation of the needle.
        cout << 0 << '\n';
        return 0;
    }

    array<int, 26> needed{};
    array<int, 26> window{};
    for (char letter : needle) {
        ++needed[letter - 'a'];
    }
    for (int index = 0; index < window_length; ++index) {
        ++window[haystack[index] - 'a'];
    }

    const DoubleRollingHash haystack_hash(haystack);
    unordered_set<uint64_t> distinct_matches;
    distinct_matches.reserve(static_cast<size_t>(text_length) * 2 + 1);

    // Every window has the correct length.  Its frequency table tells us
    // whether it is some permutation of the needle, while the ordered rolling
    // hash tells different matching permutations apart.
    for (int left = 0; left + window_length <= text_length; ++left) {
        if (window == needed) {
            distinct_matches.insert(pack_hash(
                haystack_hash.get_hash(left, left + window_length)));
        }

        // Slide one position: remove the old first letter and add the new last
        // letter.  Guard the final iteration because there is no next window.
        if (left + window_length < text_length) {
            --window[haystack[left] - 'a'];
            ++window[haystack[left + window_length] - 'a'];
        }
    }

    cout << distinct_matches.size() << '\n';
    return 0;
}
