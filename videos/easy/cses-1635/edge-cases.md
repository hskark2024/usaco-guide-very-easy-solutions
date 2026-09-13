# Edge-case checklist

- No denomination can reach the target: answer `0`.
- One denomination divides the target: exactly one repeated sequence.
- A coin equals the target: append it to the empty sequence.
- Coins larger than the current sum must be skipped.
- Different orders of the same chosen coins count separately.
- The empty sequence is a base state, not an answer because the target is positive.
- Every addition is reduced modulo `1,000,000,007`.
- The target may be one million, so use iterative DP rather than recursion.
- Keep the sum loop outside the coin loop.
