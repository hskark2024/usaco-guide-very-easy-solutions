#include <iostream>
#include <string>
#include <vector>
using namespace std;

namespace {
constexpr long long MODULUS = 998244353;

long long power_modulo(long long base, int exponent) {
    long long result = 1;
    while (exponent > 0) {
        if (exponent & 1) {
            result = result * base % MODULUS;
        }
        base = base * base % MODULUS;
        exponent >>= 1;
    }
    return result;
}
}  // namespace

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int number_count, query_count;
    string record;
    cin >> number_count >> query_count >> record;

    // If record[i] is '?', the (i + 2)-nd inserted number must be strictly
    // inside the current minimum and maximum. There are exactly i possible
    // ranks for it. At i = 0 there are no interior ranks, so the answer is 0.
    // A '<' or '>' fixes the new extreme and contributes one choice.
    vector<long long> inverse(max(2, number_count), 1);
    for (int factor = 1; factor <= number_count - 2; ++factor) {
        inverse[factor] = power_modulo(factor, MODULUS - 2);
    }

    long long product = 1;
    for (int index = 1; index < number_count - 1; ++index) {
        if (record[index] == '?') {
            product = product * index % MODULUS;
        }
    }

    auto print_answer = [&]() {
        // The second inserted value is necessarily a new minimum or maximum.
        // Therefore a question mark in the first recorded position makes the
        // entire record impossible, regardless of every later character.
        cout << (record[0] == '?' ? 0 : product) << '\n';
    };

    print_answer();
    while (query_count--) {
        int position;
        char replacement;
        cin >> position >> replacement;
        --position;

        // Position zero is handled only by print_answer. For every later
        // position, remove its old factor and insert its new factor. Since all
        // factors are below the prime modulus, modular inverses are valid.
        if (position > 0 && record[position] == '?') {
            product = product * inverse[position] % MODULUS;
        }
        if (position > 0 && replacement == '?') {
            product = product * position % MODULUS;
        }

        record[position] = replacement;
        print_answer();
    }

    return 0;
}
