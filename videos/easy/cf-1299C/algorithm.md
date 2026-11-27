# Algorithm derivation

1. Start with an empty stack of `(sum,length)` blocks.
2. Push each input amount as `(amount,1)`.
3. While the last two averages decrease, merge their sums and lengths.
4. Test `left.sum/left.length > right.sum/right.length` by cross multiplication.
5. When input ends, block averages are nondecreasing.
6. Print each block average exactly `length` times.

Equivalently, the blocks are edges of the lower convex hull of prefix-sum points, and their averages are the edge slopes.
