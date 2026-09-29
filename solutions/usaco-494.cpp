#include <algorithm>
#include <cstdio>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

struct Cow {
    long long height;
    long long weight;
    long long strength;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // The original USACO judge uses files.  Standard input remains available
    // for local verification and for modern online-judge mirrors.
    if (FILE *input_file = fopen("guard.in", "r")) {
        fclose(input_file);
        freopen("guard.in", "r", stdin);
        freopen("guard.out", "w", stdout);
    }

    int cow_count;
    long long required_height;
    cin >> cow_count >> required_height;

    vector<Cow> cows(cow_count);
    for (Cow &cow : cows) {
        cin >> cow.height >> cow.weight >> cow.strength;
    }

    const int state_count = 1 << cow_count;

    // height[mask] depends only on which cows are present, not on their order.
    // Precomputing it keeps the final answer scan and transitions simple.
    vector<long long> height(state_count, 0);

    // safety[mask] is the largest possible safety factor among all stable
    // orderings of exactly the cows in mask.  A value of -1 means no stable
    // ordering exists.  A safety factor is the minimum unused carrying
    // capacity anywhere in the stack.
    vector<long long> safety(state_count, -1);

    // An empty stack has no limiting cow.  A very large value acts as
    // infinity when the first cow is added.
    safety[0] = numeric_limits<long long>::max() / 4;

    for (int mask = 1; mask < state_count; ++mask) {
        // Recover the total height in O(1) from one smaller subset.
        const int lowest_bit = mask & -mask;
        const int lowest_cow = __builtin_ctz(lowest_bit);
        height[mask] = height[mask ^ lowest_bit] + cows[lowest_cow].height;

        for (int top_cow = 0; top_cow < cow_count; ++top_cow) {
            const int top_bit = 1 << top_cow;
            if ((mask & top_bit) == 0) {
                continue;
            }

            const int lower_stack = mask ^ top_bit;
            if (safety[lower_stack] < 0) {
                // This lower stack cannot stand, so adding a cow cannot fix it.
                continue;
            }

            // Put top_cow on top of the best ordering of lower_stack.
            // Every cow below loses top_cow's weight from its spare capacity.
            // The new cow is also limited by its own strength.
            const long long lower_margin =
                safety[lower_stack] - cows[top_cow].weight;
            const long long candidate =
                min(lower_margin, cows[top_cow].strength);

            // Negative margin means some cow is overloaded.  Keeping -1 for
            // such states makes the validity test explicit.
            if (candidate >= 0) {
                safety[mask] = max(safety[mask], candidate);
            }
        }
    }

    long long best_safety = -1;
    for (int mask = 1; mask < state_count; ++mask) {
        if (height[mask] >= required_height) {
            best_safety = max(best_safety, safety[mask]);
        }
    }

    if (best_safety < 0) {
        cout << "Mark is too tall\n";
    } else {
        cout << best_safety << '\n';
    }
    return 0;
}
