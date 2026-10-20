#include <algorithm>
#include <cstdio>
#include <iostream>
#include <set>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Keep USACO's original file interface when cardgame.in is present, while
    // retaining standard input/output for repository tests and other judges.
    if (FILE *input_file = fopen("cardgame.in", "r")) {
        fclose(input_file);
        freopen("cardgame.in", "r", stdin);
        freopen("cardgame.out", "w", stdout);
    }

    int round_count;
    cin >> round_count;

    vector<int> elsie(round_count);
    vector<bool> belongs_to_elsie(2 * round_count + 1, false);
    for (int &card : elsie) {
        cin >> card;
        belongs_to_elsie[card] = true;
    }

    // The deck is split without repetition, so Bessie's hand is exactly the
    // complement of Elsie's cards among 1..2N.
    multiset<int> bessie_hand;
    for (int card = 1; card <= 2 * round_count; ++card) {
        if (!belongs_to_elsie[card]) bessie_hand.insert(card);
    }

    // high_prefix[k] is the maximum number of wins possible in the first k
    // rounds if those rounds use the rule "larger card wins."
    vector<int> high_prefix(round_count + 1, 0);
    multiset<int> available = bessie_hand;
    for (int round = 0; round < round_count; ++round) {
        high_prefix[round + 1] = high_prefix[round];

        // The smallest card strictly larger than Elsie's wins now while
        // preserving every larger card for harder future opponents.
        auto winning_card = available.upper_bound(elsie[round]);
        if (winning_card != available.end()) {
            ++high_prefix[round + 1];
            available.erase(winning_card);
        }

        // If no winning card exists, we do not consume a card in this helper
        // matching. We only count how many wins a prefix can support; losing
        // cards can be assigned afterward to rounds that score no point.
    }

    // low_suffix[k] is the maximum number of wins in rounds k..N-1 when the
    // smaller card wins. Process backward so every stored value is a suffix.
    vector<int> low_suffix(round_count + 1, 0);
    available = bessie_hand;
    for (int round = round_count - 1; round >= 0; --round) {
        low_suffix[round] = low_suffix[round + 1];

        // lower_bound finds the first card not smaller than Elsie's. Stepping
        // left gives the largest valid winning card, which wastes the least
        // useful low card and is therefore the greedy choice.
        auto first_not_smaller = available.lower_bound(elsie[round]);
        if (first_not_smaller != available.begin()) {
            auto winning_card = prev(first_not_smaller);
            ++low_suffix[round];
            available.erase(winning_card);
        }
    }

    int answer = 0;
    for (int split = 0; split <= round_count; ++split) {
        // Rounds [0,split) use high-card wins and [split,N) use low-card wins.
        // The standard ordered-card exchange argument guarantees the two
        // maximum matching sizes can be realized together; losing rounds take
        // whatever cards remain. Splits 0 and N cover switching immediately
        // and never switching.
        answer = max(answer, high_prefix[split] + low_suffix[split]);
    }

    cout << answer << '\n';
    return 0;
}
