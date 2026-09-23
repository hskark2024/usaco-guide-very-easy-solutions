# Algorithm derivation

1. Maintain the best length and final index for each ending value.
2. At position `i` with value `x`, look up the best chain ending at `x-1`.
3. Set the candidate to that length plus one, or one if it does not exist.
4. Save the predecessor's final index in `parent[i]`.
5. Update the record for `x` if the candidate is longer.
6. Track the globally longest final index.
7. Follow parent pointers and reverse the recovered one-based indices.
