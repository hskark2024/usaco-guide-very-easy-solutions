# Edge-case checklist

- One coin: print exactly its value.
- Duplicate values: separate physical coins may combine.
- Several subsets produce the same total: print that total once.
- Reachable totals may contain large gaps.
- The maximum total uses every coin.
- Do not print zero; it represents the empty subset.
- Scan sums downward so one coin is never reused in its own pass.
- Size the table through the sum of all coin values.
- Scan final indices upward to satisfy sorted output.
