# Edge-Case Checklist

- The empty subset creates sum zero, but zero is not printed.
- A single coin produces exactly one positive sum.
- Equal-valued physical coins may both be selected.
- Descending order prevents one coin from being reused.
- Some sums may remain unreachable, creating gaps.
- The maximum tracked sum is the total of all coins, at most `100000`.
- Scanning output positions upward automatically sorts the sums.
