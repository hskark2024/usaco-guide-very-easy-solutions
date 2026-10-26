# Algorithm derivation

For a segment with sum `S` and length `len`, applying `x -> b*x+c` produces `b*S+c*len`. Store that new sum immediately and delay the per-element work.

Represent a pending function as `(mul,add)`. If an old pending function is `g(x)=m*x+a` and a new function is `f(x)=b*x+c`, the node must store `f(g(x))=(b*m)x+(b*a+c)`. Apply every operation modulo `998244353`.

Push the composed tag to children before partial recursion. Build costs `O(N)`; every update and sum query costs `O(log N)` with `O(N)` memory.
