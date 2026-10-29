# Algorithm derivation

Prefix products would need modular division, which is invalid for a composite modulus or a zero. A segment tree avoids division but is too slow for twenty million queries.

A disjoint sparse table precomputes suffixes and prefixes around every power-of-two split. The highest differing bit of the two endpoints chooses the one split crossed by the query, so two saved products answer it in constant time.
