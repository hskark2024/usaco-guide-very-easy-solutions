# Algorithm derivation

1. Define `f(x) = sum(abs(height[i] - x) * cost[i])`.
2. Observe that each term is convex and therefore `f` is convex.
3. Search integer heights from zero through the maximum input height.
4. At `mid`, compare `f(mid)` and `f(mid + 1)`.
5. Keep `[low, mid]` if the first is no larger; otherwise keep `[mid + 1, high]`.
6. Print `f(low)` when the interval becomes one point.

The comparison reads the local direction of a convex curve, so it never discards every global minimum.
