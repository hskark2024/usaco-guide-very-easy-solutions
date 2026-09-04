# Test-case walkthroughs

## Duplicate extremes

Start with `-3 0 1 3`, then insert another `3`.

- First pop-maximum prints `3`; one copy remains.
- Second pop-maximum also prints `3`.

## Both signs

After inserting `-2` and another `1`, the sorted state is `-3 -2 0 1 1`.

- Two pop-minimum queries print `-3`, then `-2`.
- A pop-maximum query prints one `1`, leaving the other copy.

## Initially empty

When `N = 0`, the first query may insert a value. The official guarantee prevents a removal before at least one value exists.
