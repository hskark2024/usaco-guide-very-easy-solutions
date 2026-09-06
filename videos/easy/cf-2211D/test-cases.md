# Test-case walkthroughs

## Official all-zero case

For `b = [0,0,0]`, every residual mask is zero. Every recovered bit count stays zero, so the construction outputs `[0,0,0]`.

## Official five-element case

For `b = [22,24,10,1,0]`, the one's bit has frequency `4`, while the two's and four's bits each have frequency `3`. Placing each bit in the first required positions constructs `[7,7,7,1,0]`, a valid answer with the same AND-array.

## One repeated value

If all ten source values equal `13`, bits zero, two, and three each have frequency ten. The largest residual immediately reveals mask `13`, and the canonical output is ten copies of `13`.

## Single element

When `n=1`, `b[1]` is simply the unknown element. The descending sweep records each set bit with frequency one and reconstructs that same value.

## Bits with different frequencies

For source `[3,1,0]`, bit zero occurs twice and bit one occurs once. The sweep discovers mask `1` at `k=2`, removes it, then discovers mask `2` at `k=1`.
