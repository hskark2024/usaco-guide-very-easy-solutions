# Algorithm derivation

Recursively split the static array. At every split, save ordered combinations from each left index through the midpoint and from just after the midpoint through each right index.

For a query, descend until its endpoints first lie on different sides. The two stored aggregates cover the interval in order, and one `Secret(left,right)` call joins them. A singleton returns its original value.

Preprocessing uses `O(N log N)` time, calls, and memory. A query uses `O(log N)` comparisons and at most one `Secret` call.
