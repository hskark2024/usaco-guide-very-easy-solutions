#include <cstdint>
#include <iostream>

using namespace std;

// Every answer is reduced by this prime modulus.
constexpr int64_t MOD = 1'000'000'007LL;

// Binary exponentiation reads the exponent one binary digit at a time.
// This needs only O(log exponent) multiplications instead of exponent steps.
int64_t mod_pow(int64_t base, int64_t exponent) {
    // The input base is already at most 1e9, but reducing here makes the
    // helper correct and reusable even for larger nonnegative bases.
    base %= MOD;
    int64_t result = 1;

    while (exponent > 0) {
        // If the current low bit is 1, this power of two belongs in the
        // exponent's binary expansion, so include the current base power.
        if (exponent & 1LL) {
            result = result * base % MOD;
        }

        // After squaring, base represents the next power:
        // a^(1), a^(2), a^(4), a^(8), and so on.
        base = base * base % MOD;

        // Remove the binary digit that we just processed.
        exponent >>= 1LL;
    }

    // Starting from 1 correctly handles every exponent-zero query,
    // including the statement's explicit convention that 0^0 = 1.
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int query_count;
    cin >> query_count;

    while (query_count--) {
        int64_t base, exponent;
        cin >> base >> exponent;

        // Each query is independent, so no state is carried between them.
        cout << mod_pow(base, exponent) << '\n';
    }

    return 0;
}
