#include <array>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
using namespace std;

// Two independent polynomial hashes make substring comparisons constant time.
// A single modular hash is usually fine in a closed judge, but using two makes
// an accidental collision dramatically less likely.
class DoubleHash {
  private:
    static constexpr long long MOD_1 = 1'000'000'007LL;
    static constexpr long long MOD_2 = 1'000'000'009LL;
    static constexpr long long BASE = 911'382'323LL;

    vector<long long> prefix_1, prefix_2;
    vector<long long> power_1, power_2;

  public:
    explicit DoubleHash(const string &text)
        : prefix_1(text.size() + 1), prefix_2(text.size() + 1),
          power_1(text.size() + 1, 1), power_2(text.size() + 1, 1) {
        for (int i = 0; i < static_cast<int>(text.size()); ++i) {
            const int value = text[i] - 'a' + 1;
            prefix_1[i + 1] = (prefix_1[i] * BASE + value) % MOD_1;
            prefix_2[i + 1] = (prefix_2[i] * BASE + value) % MOD_2;
            power_1[i + 1] = power_1[i] * BASE % MOD_1;
            power_2[i + 1] = power_2[i] * BASE % MOD_2;
        }
    }

    // Return a position-independent fingerprint of text[left, right).
    pair<long long, long long> slice(int left, int right) const {
        long long first =
            (prefix_1[right] - prefix_1[left] * power_1[right - left]) % MOD_1;
        long long second =
            (prefix_2[right] - prefix_2[left] * power_2[right - left]) % MOD_2;
        if (first < 0) first += MOD_1;
        if (second < 0) second += MOD_2;
        return {first, second};
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string pattern, received;
    cin >> pattern >> received;

    int count_zero = 0;
    for (char symbol : pattern) count_zero += symbol == '0';
    int count_one = static_cast<int>(pattern.size()) - count_zero;

    // Enumerate the replacement length of the more frequent symbol.  If it
    // is called 0, there can be at most |received| / count_zero candidates,
    // and count_zero is at least half the pattern length.  This is what makes
    // the total number of inspected pattern symbols linear in |received|.
    if (count_zero < count_one) {
        for (char &symbol : pattern) symbol = (symbol == '0' ? '1' : '0');
        swap(count_zero, count_one);
    }

    const DoubleHash hashes(received);
    const long long received_length = received.size();
    long long answer = 0;

    for (long long length_zero = 1;
         length_zero * count_zero < received_length;
         ++length_zero) {
        const long long remaining = received_length - length_zero * count_zero;

        // The other replacement must also have a positive integral length.
        if (remaining <= 0 || remaining % count_one != 0) continue;
        const long long length_one = remaining / count_one;
        if (length_one <= 0) continue;

        const array<long long, 2> lengths = {length_zero, length_one};
        array<pair<long long, long long>, 2> wanted{};
        array<bool, 2> learned = {false, false};
        long long position = 0;
        bool valid = true;

        // The first occurrence of each symbol chooses its replacement.  Every
        // later occurrence must have the same double hash.
        for (char symbol_character : pattern) {
            const int symbol = symbol_character - '0';
            const long long next_position = position + lengths[symbol];
            const auto current = hashes.slice(
                static_cast<int>(position), static_cast<int>(next_position));

            if (!learned[symbol]) {
                wanted[symbol] = current;
                learned[symbol] = true;
            } else if (wanted[symbol] != current) {
                valid = false;
                break;
            }
            position = next_position;
        }

        if (!valid) continue;

        // Different lengths already imply different strings.  Equal lengths
        // need an explicit content check because r0 and r1 may not be equal.
        if (length_zero == length_one && wanted[0] == wanted[1]) continue;
        ++answer;
    }

    cout << answer << '\n';
    return 0;
}
