# Edge-case checklist

- `n = 0` or `n = 1`: there is no pair with gcd greater than one.
- Equal endpoints: `(y,y)` is valid for every `y > 1` and is included.
- Reversed order: only the representation with `x <= y` is counted.
- Prime larger endpoint: only `(y,y)` is non-coprime, since `y - phi(y) = 1`.
- Composite endpoint: several smaller values may share a factor and are all included.
- Large answer: store prefix counts in `long long`.
- Multiple test cases: preserve the required `Case i:` numbering.
