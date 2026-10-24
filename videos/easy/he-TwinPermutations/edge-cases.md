# Edge-case checklist

- Permutations are identical.
- Permutations are reversed.
- A query selects one element.
- A query selects both full permutations.
- The selected ranges contain the same set in different orders.
- The selected ranges have no shared values.
- The second range starts at position one, creating a prefix-zero event.
- Query length equals one or `n`.
- There are `100,000` values and `100,000` queries.
