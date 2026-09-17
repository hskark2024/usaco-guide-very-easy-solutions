#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int book_count, budget;
    cin >> book_count >> budget;
    vector<int> price(book_count), pages(book_count);
    for (int &value : price) cin >> value;
    for (int &value : pages) cin >> value;

    // best[money] is the most pages purchasable using only the processed
    // books while spending AT MOST money.  Zero pages are feasible at every
    // capacity by buying nothing; a separate impossible-state marker is not
    // needed for this at-most-budget version of 0/1 knapsack.
    vector<int> best(budget + 1, 0);
    for (int book = 0; book < book_count; ++book) {
        // Scan DOWNWARD so best[money - price] still refers to the previous
        // book row.  If we scanned upward, one book could contribute pages
        // repeatedly, although the shop permits buying it only once.
        for (int money = budget; money >= price[book]; --money) {
            // Every legal choice either skips this book (the existing state)
            // or buys it alongside a previously processed selection.
            best[money] = max(best[money],
                              best[money - price[book]] + pages[book]);
        }
    }

    cout << best[budget] << '\n';
    return 0;
}
