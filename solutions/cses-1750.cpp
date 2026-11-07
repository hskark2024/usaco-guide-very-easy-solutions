#include <array>
#include <iostream>
#include <vector>
using namespace std;

// CSES 1750: Planets Queries I
//
// Every planet has exactly one outgoing teleport.  Repeating that teleport
// creates a functional-graph walk, possibly entering a cycle.  Binary lifting
// answers huge step counts without needing to identify the cycle explicitly.
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int planet_count, query_count;
    cin >> planet_count >> query_count;

    // The largest query count is 10^9, whose highest possible set bit is 29.
    // Exactly 30 columns therefore cover every official query without storing
    // unused levels or spending extra time composing them.
    constexpr int LOG = 30;
    vector<array<int, LOG>> destination(planet_count + 1);

    // Level zero is one teleport from each planet.
    for (int planet = 1; planet <= planet_count; ++planet) {
        cin >> destination[planet][0];
    }

    // Compose two 2^(level-1)-step trips to obtain one 2^level-step trip.
    // All table entries remain valid planet numbers because every planet has
    // exactly one outgoing teleport.
    for (int level = 1; level < LOG; ++level) {
        for (int planet = 1; planet <= planet_count; ++planet) {
            const int middle = destination[planet][level - 1];
            destination[planet][level] = destination[middle][level - 1];
        }
    }

    while (query_count--) {
        int planet;
        long long teleport_count;
        cin >> planet >> teleport_count;

        // The set bits form a disjoint sum equal to teleport_count.  Applying
        // their precomputed jumps therefore follows exactly that many edges.
        for (int level = 0; level < LOG; ++level) {
            if ((teleport_count >> level) & 1LL) {
                planet = destination[planet][level];
            }
        }
        cout << planet << '\n';
    }
    return 0;
}
