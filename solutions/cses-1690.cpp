#include <cstdint>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    constexpr int MODULO = 1'000'000'007;

    int city_count;
    int flight_count;
    cin >> city_count >> flight_count;

    // edge_multiplicity[a][b] preserves parallel directed flights if they
    // occur. incoming_mask[b] lets each transition inspect only cities that
    // can actually fly into b.
    vector<vector<int>> edge_multiplicity(
        city_count,
        vector<int>(city_count, 0)
    );
    vector<uint32_t> incoming_mask(city_count, 0);

    for (int flight = 0; flight < flight_count; ++flight) {
        int from;
        int to;
        cin >> from >> to;
        --from;
        --to;
        ++edge_multiplicity[from][to];
        incoming_mask[to] |= uint32_t{1} << from;
    }

    const uint32_t state_count = uint32_t{1} << city_count;
    const uint32_t all_cities = state_count - 1;
    const uint32_t start_bit = 1;
    const uint32_t destination_bit = uint32_t{1} << (city_count - 1);

    // dp[mask][last] counts routes that start at city 0, visit exactly mask,
    // and finish at last.  A flat array has less overhead than 2^N vectors.
    vector<int> dp(static_cast<size_t>(state_count) * city_count, 0);
    auto cell = [&](uint32_t mask, int last) -> int& {
        return dp[static_cast<size_t>(mask) * city_count + last];
    };
    cell(start_bit, 0) = 1;

    for (uint32_t mask = 1; mask < state_count; ++mask) {
        // Every route must contain its fixed starting city.
        if ((mask & start_bit) == 0) {
            continue;
        }

        // The destination must be visited last.  Any non-full state already
        // containing it can never lead to a valid Hamiltonian route.
        if ((mask & destination_bit) != 0 && mask != all_cities) {
            continue;
        }

        // At the full state we only need the destination answer.  Otherwise
        // consider each included non-start, non-destination city as the end.
        uint32_t possible_ends = mask & ~start_bit & ~destination_bit;
        if (mask == all_cities) {
            possible_ends = destination_bit;
        }

        while (possible_ends != 0) {
            const int last = __builtin_ctz(possible_ends);
            possible_ends &= possible_ends - 1;

            const uint32_t previous_mask = mask ^ (uint32_t{1} << last);
            uint32_t possible_previous =
                incoming_mask[last] & previous_mask;

            int64_t route_count = 0;
            while (possible_previous != 0) {
                const int previous = __builtin_ctz(possible_previous);
                possible_previous &= possible_previous - 1;

                // Remove last from the route, then append one of the directed
                // flights previous -> last.  Modulo reduction on every add
                // keeps the accumulator comfortably bounded.
                route_count += static_cast<int64_t>(
                    cell(previous_mask, previous)
                ) * edge_multiplicity[previous][last];
                route_count %= MODULO;
            }
            cell(mask, last) = static_cast<int>(route_count);
        }
    }

    cout << cell(all_cities, city_count - 1) << '\n';
    return 0;
}
