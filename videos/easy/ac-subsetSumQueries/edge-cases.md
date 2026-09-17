# Edge-Case Checklist

- The empty subset keeps `ways[0] = 1`.
- A ball with value larger than `K` changes no tracked coefficient.
- Equal-valued balls remain distinguishable and create binomial multiplicities.
- Removing one duplicate leaves the other copies represented.
- Subtraction may become negative before adding the modulus.
- Counts can wrap around the modulus many times.
- Every removal is valid by the problem guarantee.
- The answer is printed after every operation, including irrelevant large values.
