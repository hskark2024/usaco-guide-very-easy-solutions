# Algorithm derivation

1. Let `m` be the needle length; only haystack windows of length `m` matter.
2. Count the 26 letters in the needle and the first window.
3. Build two polynomial prefix-hash arrays for the haystack.
4. If a window's frequency table matches the needle's, it is a permutation.
5. Get that window's ordered double hash in constant time.
6. Pack the two residues and insert them into a set.
7. Slide by removing the old left letter and adding the new right letter.
8. Return the number of distinct fingerprints in the set.

Letter counts answer “is it a permutation?” Hashes answer “have we seen this exact ordering already?”
