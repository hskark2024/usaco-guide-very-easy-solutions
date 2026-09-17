# Test-case walkthroughs

## Small mixed collection

For coins `2, 3, 5`, the positive totals are `2, 3, 5, 7, 8, 10`. Sum five has two constructions, but it appears only once because the output is a set of totals.

## Duplicate values

Coins `2, 2, 2` reach `2, 4, 6`. Each coin is one-use, while separate passes allow two or three physical copies to combine.

## Gapped totals

Coins `5, 10` reach only `5, 10, 15`. The boolean table preserves gaps.

## Independent verifier

For random lists of at most twelve coins, the oracle enumerates every nonempty subset mask, inserts its sum into a Python set, sorts the set, and compares both the reported count and all printed values.
