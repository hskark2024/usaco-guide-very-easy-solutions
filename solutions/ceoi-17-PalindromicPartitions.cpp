#include <algorithm>
#include <cstdint>
#include <iostream>
#include <string>
using namespace std;

using uint64 = uint64_t;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int test_count;
    cin >> test_count;

    while (test_count--) {
        string text;
        cin >> text;

        int left = 0;
        int right = static_cast<int>(text.size()) - 1;
        int chunk_count = 0;

        // Two independent 64-bit polynomial hashes are updated from opposite
        // ends.  Unsigned overflow is defined modulo 2^64 in C++.
        constexpr uint64 BASE_1 = 1'000'000'007ULL;
        constexpr uint64 BASE_2 = 1'000'000'009ULL;

        while (left <= right) {
            uint64 left_hash_1 = 0;
            uint64 left_hash_2 = 0;
            uint64 right_hash_1 = 0;
            uint64 right_hash_2 = 0;
            uint64 power_1 = 1;
            uint64 power_2 = 1;
            bool removed_matching_pair = false;

            // Try chunk lengths 1, 2, ... and stop at the first equal outer
            // pair.  Shortest equal outer chunks leave the most characters
            // available for additional pairs, which is the greedy optimum.
            for (int offset = 0; left + offset < right - offset; ++offset) {
                const uint64 left_value = text[left + offset] - 'a' + 1;
                const uint64 right_value = text[right - offset] - 'a' + 1;

                // The left chunk grows on its right side.
                left_hash_1 = left_hash_1 * BASE_1 + left_value;
                left_hash_2 = left_hash_2 * BASE_2 + left_value;

                // The right chunk grows on its left side, so the new letter
                // receives the highest power instead of being appended.
                right_hash_1 += right_value * power_1;
                right_hash_2 += right_value * power_2;
                power_1 *= BASE_1;
                power_2 *= BASE_2;

                if (left_hash_1 != right_hash_1
                    || left_hash_2 != right_hash_2) {
                    continue;
                }

                const int length = offset + 1;
                const int right_chunk_start = right - length + 1;

                // The hashes are only a fast filter.  Confirming equal bytes
                // gives deterministic correctness even if a collision occurs.
                if (!equal(text.begin() + left,
                           text.begin() + left + length,
                           text.begin() + right_chunk_start)) {
                    continue;
                }

                chunk_count += 2;
                left += length;
                right -= length;
                removed_matching_pair = true;
                break;
            }

            if (!removed_matching_pair) {
                // Whatever remains becomes the single center chunk.  A center
                // chunk may contain any nonempty string.
                ++chunk_count;
                break;
            }
        }

        cout << chunk_count << '\n';
    }

    return 0;
}
