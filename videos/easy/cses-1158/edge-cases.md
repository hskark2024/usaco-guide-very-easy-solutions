# Edge-Case Checklist

- A book costing more than the budget is skipped.
- Each book is available once, even if prices are equal.
- The optimum may leave part of the budget unused.
- Buying nothing is legal and worth zero pages.
- An upward capacity scan would incorrectly allow repeated purchases.
- Up to one million total pages fit safely in a C++ `int`.
- The largest limits require about one hundred million updates.
