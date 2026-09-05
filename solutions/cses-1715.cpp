#include <array>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

constexpr long long MOD = 1'000'000'007;

// Computes base^exponent modulo MOD in O(log exponent) time.
// Fermat's little theorem lets us use this routine to find modular inverses:
// because MOD is prime, x^(MOD - 2) is the inverse of every nonzero x.
long long mod_pow(long long base, long long exponent) {
    long long result = 1;
    while (exponent > 0) {
        // A set binary bit means this power of base belongs in the answer.
        if (exponent & 1LL) {
            result = result * base % MOD;
        }

        // Squaring moves from base^(2^j) to base^(2^(j+1)).
        base = base * base % MOD;
        exponent >>= 1LL;
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string letters;
    cin >> letters;

    // Only the multiplicity of each letter matters. Swapping two equal
    // letters does not create a new string.
    array<int, 26> frequency{};
    for (char letter : letters) {
        ++frequency[letter - 'a'];
    }

    const int length = static_cast<int>(letters.size());

    // factorial[i] stores i! modulo MOD. Since length <= 1,000,000 < MOD,
    // every factorial used here is nonzero modulo MOD and can be inverted.
    vector<long long> factorial(length + 1, 1);
    for (int value = 1; value <= length; ++value) {
        factorial[value] = factorial[value - 1] * value % MOD;
    }

    // Begin with n!, which counts arrangements as if every position held a
    // distinct object. For a letter appearing c times, those c copies can be
    // reordered in c! indistinguishable ways, so divide by c!.
    long long denominator = 1;
    for (int count : frequency) {
        denominator = denominator * factorial[count] % MOD;
    }

    // Modular division by denominator is multiplication by its inverse.
    const long long inverse_denominator = mod_pow(denominator, MOD - 2);
    const long long answer = factorial[length] * inverse_denominator % MOD;

    cout << answer << '\n';
}
