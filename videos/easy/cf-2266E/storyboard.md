# Storyboard

1. Title card: a large composite number breaking into equal smaller pieces.
2. Show the operation `x -> p copies of x/p` and highlight that `p` must be prime.
3. Separate the original multiset into independent operation trees.
4. Introduce `dp[x]` and shade all states `x <= k` green with cost zero.
5. Animate one candidate first split and its `p` equal children.
6. Reveal the recurrence `dp[x] = min(1 + p * dp[x/p])`.
7. Put states on an increasing number line to explain evaluation order.
8. Show smallest-prime-factor extraction with duplicate factors skipped.
9. Walk through `8 -> 4,4 -> 2,2,2,2 -> eight 1s` for `k=1`.
10. Finish with summation, complexity, and verification cards.
