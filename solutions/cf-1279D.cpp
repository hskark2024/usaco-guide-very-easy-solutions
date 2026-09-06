#include <cstdint>
#include <iostream>
#include <vector>

using namespace std;

constexpr int64_t MOD = 998'244'353LL;
constexpr int MAX_ITEM_ID = 1'000'000;

// Binary exponentiation is used for modular division. Because MOD is prime,
// x^(MOD-2) is the multiplicative inverse of every nonzero x modulo MOD.
int64_t mod_pow(int64_t base, int64_t exponent) {
    int64_t result = 1;
    while (exponent > 0) {
        if (exponent & 1LL) result = result * base % MOD;
        base = base * base % MOD;
        exponent >>= 1LL;
    }
    return result;
}

int64_t modular_inverse(int64_t value) {
    return mod_pow(value, MOD - 2);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int child_count;
    cin >> child_count;

    // We need every item's final popularity before we can score any child's
    // list, so keep the lists while building one global frequency table.
    vector<vector<int>> wanted_items(child_count);
    vector<int> request_count(MAX_ITEM_ID + 1, 0);

    for (vector<int> &list : wanted_items) {
        int list_size;
        cin >> list_size;
        list.resize(list_size);

        for (int &item : list) {
            cin >> item;
            ++request_count[item];
        }
    }

    int64_t weighted_valid_choices = 0;

    // If child x is selected first, each item in that child's list has
    // probability 1/k_x. Once item y is chosen, request_count[y] of the n
    // possible recipient children accept it. Therefore this child's modular
    // contribution is sum(request_count[y]) / k_x.
    for (const vector<int> &list : wanted_items) {
        int64_t accepting_recipients = 0;
        for (int item : list) {
            accepting_recipients += request_count[item];
        }
        accepting_recipients %= MOD;

        weighted_valid_choices +=
            accepting_recipients * modular_inverse(list.size()) % MOD;
        weighted_valid_choices %= MOD;
    }

    // The first child x and the recipient z are each chosen uniformly and
    // independently, so the outer probability contributes a factor of 1/n^2.
    const int64_t inverse_n = modular_inverse(child_count);
    const int64_t answer =
        weighted_valid_choices * inverse_n % MOD * inverse_n % MOD;

    cout << answer << '\n';
}
