#include <cstdint>
#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int64_t number;
    cin >> number;

    int answer = 0;

    // Factor N by trial division. Because N is at most 1e12, checking
    // candidates through sqrt(N) requires at most about one million steps.
    // Composite candidates have already been divided out and add nothing.
    for (int64_t prime = 2; prime * prime <= number; ++prime) {
        if (number % prime != 0) {
            continue;
        }

        int exponent = 0;
        while (number % prime == 0) {
            number /= prime;
            ++exponent;
        }

        // Using p^1, p^2, ..., p^k costs 1+2+...+k copies of p. These powers
        // are all distinct, and smallest-first leaves room for the most moves.
        int next_power_exponent = 1;
        while (exponent >= next_power_exponent) {
            exponent -= next_power_exponent;
            ++answer;
            ++next_power_exponent;
        }
    }

    // Any remaining factor is prime with exponent one. If its exponent were
    // at least two, its square would have kept the loop running.
    if (number > 1) {
        ++answer;
    }

    cout << answer << '\n';
    return 0;
}
