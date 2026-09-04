#include <chrono>
#include <cstdint>
#include <iostream>
#include <unordered_map>
using namespace std;

struct SplitMix64Hash {
    static uint64_t mix(uint64_t x) {
        x += 0x9e3779b97f4a7c15ULL;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
        x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t seed = chrono::steady_clock::now().time_since_epoch().count();
        return mix(x + seed);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int q;
    cin >> q;
    unordered_map<uint64_t, uint64_t, SplitMix64Hash> values;
    values.reserve(static_cast<size_t>(q) * 2);

    while (q--) {
        int type;
        uint64_t key;
        cin >> type >> key;
        if (type == 0) {
            uint64_t value;
            cin >> value;
            values[key] = value;
        } else {
            auto it = values.find(key);
            cout << (it == values.end() ? 0 : it->second) << '\n';
        }
    }
    return 0;
}
