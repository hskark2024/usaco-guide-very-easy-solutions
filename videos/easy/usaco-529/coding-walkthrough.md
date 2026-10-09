# C++ coding walkthrough

1. Hash the forbidden word before processing the source.
2. Precompute both base-power arrays through `source.size()`.
3. Reserve the result string and prefix vectors once.
4. Append a letter and extend each prefix hash from its previous back value.
5. Derive suffix hashes using `prefix[end] - prefix[start] * power[length]`.
6. Run `std::equal` only after both fast hashes match.
7. Delete with `resize(start)` and keep prefix arrays at `start+1` states.
8. Output the remaining stack.
