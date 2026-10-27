#ifdef EVAL
#include "secret.h"
#else
#include <algorithm>
#include <iostream>
using namespace std;

// The downloaded JOI grader uses this associative, order-sensitive operation.
// Keeping it in the local-only branch makes this file independently testable;
// the official judge supplies its own hidden Secret function under EVAL.
int Secret(int x, int y) {
    constexpr int limit = 1'000'000'000;
    return min(limit, x + 2 * (y / 2));
}
#endif

namespace {

constexpr int MAX_N = 1000;
constexpr int MAX_LEVELS = 11;

int element_count;
int original_values[MAX_N];

// At a recursion level, combined[level][i] stores the ordered combination
// from i to that segment's midpoint (left half) or from midpoint+1 to i
// (right half). Disjoint segments at one level occupy disjoint indices.
int combined[MAX_LEVELS][MAX_N];

void build_crossing_answers(int left, int right, int level) {
    if (left == right) {
        return;
    }

    const int middle = (left + right) / 2;

    // Build left aggregates in the only valid order:
    // A[i] Secret A[i+1] Secret ... Secret A[middle].
    combined[level][middle] = original_values[middle];
    for (int i = middle - 1; i >= left; --i) {
        combined[level][i] = Secret(original_values[i],
                                    combined[level][i + 1]);
    }

    // Build right aggregates in forward order:
    // A[middle+1] Secret ... Secret A[i].
    combined[level][middle + 1] = original_values[middle + 1];
    for (int i = middle + 2; i <= right; ++i) {
        combined[level][i] = Secret(combined[level][i - 1],
                                    original_values[i]);
    }

    build_crossing_answers(left, middle, level + 1);
    build_crossing_answers(middle + 1, right, level + 1);
}

}  // namespace

// These two functions are the interface required by the official JOI grader.
void Init(int N, int A[]) {
    element_count = N;
    for (int i = 0; i < N; ++i) {
        original_values[i] = A[i];
    }
    build_crossing_answers(0, N - 1, 0);
}

int Query(int L, int R) {
    if (L == R) {
        // A one-element range needs no call to the expensive Secret function.
        return original_values[L];
    }

    int left = 0;
    int right = element_count - 1;
    int level = 0;

    while (left < right) {
        const int middle = (left + right) / 2;
        if (L <= middle && middle < R) {
            // The first recursion split crossed by the query has both halves
            // precomputed. Associativity allows exactly one final combination.
            return Secret(combined[level][L], combined[level][R]);
        }
        if (R <= middle) {
            right = middle;
        } else {
            left = middle + 1;
        }
        ++level;
    }

    return original_values[L];
}

#ifndef EVAL
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int size;
    cin >> size;
    int values[MAX_N];
    for (int i = 0; i < size; ++i) {
        cin >> values[i];
    }
    Init(size, values);

    int query_count;
    cin >> query_count;
    while (query_count--) {
        int left, right;
        cin >> left >> right;
        cout << Query(left, right) << '\n';
    }
    return 0;
}
#endif
