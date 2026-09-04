# Test-case walkthroughs

## Official example

For `n = 3` and `m = 2`, draw two stars and two bars. Choosing the two bar positions among four slots gives `C(4,2) = 6`.

## One child

For `n = 1` and any positive `m`, there are no bars. The only distribution gives every apple to that child, so the answer is `1`.

## One apple

For `m = 1`, exactly one of the `n` children receives the apple. The formula `C(n, n-1)` returns `n`.
