# Storyboard

1. **Hook — the longest subsequence**: Show cards `1` through `n-1` and a product target of `1 mod n`.
2. **Reject non-coprimes**: Move values sharing a factor with `n` into a locked bin.
3. **Try every unit**: Multiply the remaining cards while reducing modulo `n`.
4. **The one-removal trick**: If the product is `p`, remove the card labeled `p`.
5. **Proof of maximum size**: Show that zero removals or exactly one removal meets the lower bound.
6. **Examples**: Trace `n=5`, `n=8`, and `n=2`.
7. **C++ implementation**: Highlight gcd filtering, modular multiplication, and stable output.
