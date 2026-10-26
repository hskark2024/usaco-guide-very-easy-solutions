# Edge-case checklist

- One-element sequence and one-element intervals.
- Full-array updates followed by small subrange queries.
- Identity function `x -> x`.
- Pure addition with multiplier one.
- Pure multiplication with addend zero.
- Several noncommuting affine updates on the same node.
- Partial overlap after a full-node update forces a correct push.
- Values near `998244353` and products requiring modular reduction.
- `N=Q=500,000` without recursion or memory overflow.
