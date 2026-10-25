# Algorithm derivation

A range addition is two difference-array boundary events: `+x` at `left` and `-x` at `right+1`. For a prefix ending at `p`, an event beginning at `l` contributes `x*(p-l+1) = p*x - x*(l-1)`. Store the `x` coefficient in one Fenwick tree and `x*(l-1)` in another.

The prefix formula is `p * coefficientPrefix(p) - correctionPrefix(p)`. Subtract two such prefixes for a range sum. Each command costs `O(log n)` time and the two trees use `O(n)` memory.
