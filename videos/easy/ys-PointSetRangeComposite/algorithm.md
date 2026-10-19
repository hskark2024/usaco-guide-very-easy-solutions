# Algorithm derivation

An affine function is fully described by `(a,b)`. If `first(x)=a*x+b` and `second(x)=c*x+d`, then `second(first(x))=(c*a)x+(c*b+d)`. This operation is associative and has identity `(1,0)`, so it is a valid segment-tree combiner.

The combiner is order-sensitive. An iterative range query therefore keeps a forward left accumulator and a backward right accumulator. A point replacement and a range composition each take `O(log n)` time.
