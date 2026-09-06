#include <cstdint>
#include <iostream>

using namespace std;

// The final answer is taken modulo this prime.
constexpr int64_t MOD = 1'000'000'007LL;

// Fast exponentiation computes base^exponent with only O(log exponent)
// multiplications. Reducing after every multiplication keeps the values small.
int64_t mod_pow(int64_t base, int64_t exponent, int64_t modulus) {
    base %= modulus;
    int64_t result = 1;

    while (exponent > 0) {
        // A set binary digit means this power of base belongs in the answer.
        if (exponent & 1LL) {
            result = result * base % modulus;
        }

        // Squaring moves from base^(2^j) to base^(2^(j+1)).
        base = base * base % modulus;
        exponent >>= 1LL;
    }

    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int query_count;
    cin >> query_count;

    while (query_count--) {
        int64_t a, b, c;
        cin >> a >> b >> c;

        // Fermat's little theorem lets us reduce an exponent modulo MOD - 1
        // when the base is not divisible by MOD. Here a <= 1e9, so every
        // positive a is automatically smaller than MOD and therefore coprime
        // to MOD.
        const int64_t reduced_exponent = mod_pow(b, c, MOD - 1);

        // The only non-coprime base allowed by the constraints is a = 0.
        // The true exponent b^c is zero exactly when b = 0 and c > 0. The
        // statement also defines 0^0 as 1, so exponent_is_zero handles every
        // zero-base corner case before we use the reduced exponent.
        const bool exponent_is_zero = (b == 0 && c > 0);
        if (a == 0 && !exponent_is_zero) {
            cout << 0 << '\n';
            continue;
        }

        // mod_pow returns 1 for exponent zero, which correctly covers a^0,
        // including the problem's explicit convention that 0^0 equals 1.
        cout << mod_pow(a, reduced_exponent, MOD) << '\n';
    }
}
