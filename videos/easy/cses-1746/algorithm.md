# Algorithm derivation

1. Let `previous[v]` count matching prefixes ending at value `v`.
2. Initialize allowed values at position zero to one.
3. For every later position, clear `current`.
4. For each value allowed by that position, sum `previous[v-1]`, `previous[v]`, and `previous[v+1]` modulo `M`.
5. Swap the two rows.
6. Sum all counts in the final row.
