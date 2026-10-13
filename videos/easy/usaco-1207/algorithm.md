# Algorithm derivation

1. Split the movement instructions into two halves.
2. Enumerate every right subset's displacement and size.
3. Store coordinate frequencies in one hash map per right subset size.
4. Enumerate every left subset with point `p` and size `i`.
5. Compute the required right point `goal-p`.
6. In every right size `j`, add that point's frequency to `answer[i+j]`.
7. Print buckets one through `N`.
