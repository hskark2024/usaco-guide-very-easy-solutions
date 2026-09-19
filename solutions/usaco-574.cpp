#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Honor the original USACO file interface, while allowing stdin/stdout
    // when no feast.in exists, as used by the repository's local tests.
    if (FILE *input_file = fopen("feast.in", "r")) {
        fclose(input_file);
        freopen("feast.in", "r", stdin);
        freopen("feast.out", "w", stdout);
    }

    int limit, orange, lemon;
    cin >> limit >> orange >> lemon;

    // A single fullness value is not enough: drinking must happen at most
    // once. Separate layers record whether that one drink is still available.
    // Byte arrays use roughly 2*(T+1) bytes and have constant-time indexing.
    vector<unsigned char> before(limit + 1, 0), after(limit + 1, 0);
    before[0] = 1;  // Eating nothing is a valid starting state.

    for (int fullness = 0; fullness <= limit; ++fullness) {
        if (!before[fullness]) continue;
        // Fruit may be eaten repeatedly. Increasing fullness order lets a
        // newly reached larger state eat more fruit later in the same pass.
        if (fullness + orange <= limit) before[fullness + orange] = 1;
        if (fullness + lemon <= limit) before[fullness + lemon] = 1;

        // Integer division implements the required round-down. Seed every
        // legal drinking point, including zero, into the second layer.
        // We do not propagate after yet: all drinking seeds are collected first.
        after[fullness / 2] = 1;
    }

    for (int fullness = 0; fullness <= limit; ++fullness) {
        if (!after[fullness]) continue;
        if (fullness + orange <= limit) after[fullness + orange] = 1;
        if (fullness + lemon <= limit) after[fullness + lemon] = 1;
        // There is deliberately no halving transition from this layer:
        // allowing one would accidentally give Bessie a second drink.
    }

    // Water is optional, so accept either layer. The first reachable value
    // found while scanning down is exactly the greatest legal final fullness.
    for (int fullness = limit; fullness >= 0; --fullness) {
        if (before[fullness] || after[fullness]) {
            cout << fullness << '\n';
            break;
        }
    }
    return 0;
}
