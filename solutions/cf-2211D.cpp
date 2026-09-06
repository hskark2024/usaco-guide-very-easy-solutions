#include <cstdint>
#include <iostream>
#include <vector>

using namespace std;

constexpr int64_t MOD = 1'000'000'007LL;
constexpr int MAX_N = 100'000;
constexpr int BIT_COUNT = 29;

int64_t mod_pow(int64_t base, int64_t exponent) {
    int64_t result = 1;
    while (exponent > 0) {
        if (exponent & 1LL) result = result * base % MOD;
        base = base * base % MOD;
        exponent >>= 1LL;
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // C(n, k) is needed while removing a discovered bit's contribution from
    // every smaller subsequence size. Factorials make each value O(1).
    vector<int64_t> factorial(MAX_N + 1, 1);
    vector<int64_t> inverse_factorial(MAX_N + 1, 1);
    for (int value = 1; value <= MAX_N; ++value) {
        factorial[value] = factorial[value - 1] * value % MOD;
    }
    inverse_factorial[MAX_N] = mod_pow(factorial[MAX_N], MOD - 2);
    for (int value = MAX_N; value >= 1; --value) {
        inverse_factorial[value - 1] =
            inverse_factorial[value] * value % MOD;
    }

    auto choose = [&](int n, int k) -> int64_t {
        if (k < 0 || k > n) return 0;
        return factorial[n] * inverse_factorial[k] % MOD *
               inverse_factorial[n - k] % MOD;
    };

    int test_count;
    cin >> test_count;
    while (test_count--) {
        int n;
        cin >> n;

        // residual[k] stores the still-unexplained value for subsequences of
        // length k. Index 0 is unused because the input begins at length 1.
        vector<int64_t> residual(n + 1, 0);
        for (int k = 1; k <= n; ++k) cin >> residual[k];

        // count_for_bit[bit] will become the number of unknown array elements
        // that contain this bit.
        vector<int> count_for_bit(BIT_COUNT, 0);

        // Process subsequence sizes from largest to smallest. After all bits
        // with counts greater than k have been removed, residual[k] contains
        // exactly the powers of two whose bits occur in exactly k positions.
        for (int k = n; k >= 1; --k) {
            const int64_t discovered_mask = residual[k];

            // The residual is an ordinary 29-bit mask, not merely an opaque
            // residue: the promised valid input makes it smaller than 2^29,
            // which is also smaller than MOD.
            for (int bit = 0; bit < BIT_COUNT; ++bit) {
                if ((discovered_mask >> bit) & 1LL) {
                    count_for_bit[bit] = k;
                }
            }

            if (discovered_mask == 0) continue;

            // A bit present in k array elements appears in C(k, length)
            // subsequences of each smaller length. All bits discovered at the
            // same k can be removed together by multiplying that combination
            // count by their complete mask.
            for (int length = 1; length < k; ++length) {
                const int64_t contribution =
                    discovered_mask * choose(k, length) % MOD;
                residual[length] -= contribution;
                if (residual[length] < 0) residual[length] += MOD;
            }
        }

        // Only each bit's frequency matters to every AND sum. A convenient
        // canonical construction puts the bit into the first count positions.
        // Different bits may overlap freely, and every a[i] remains below 2^29.
        vector<int> answer(n, 0);
        for (int bit = 0; bit < BIT_COUNT; ++bit) {
            for (int index = 0; index < count_for_bit[bit]; ++index) {
                answer[index] |= (1 << bit);
            }
        }

        for (int index = 0; index < n; ++index) {
            if (index > 0) cout << ' ';
            cout << answer[index];
        }
        cout << '\n';
    }
}
