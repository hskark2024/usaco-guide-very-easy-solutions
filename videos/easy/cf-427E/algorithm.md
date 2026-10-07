# Algorithm derivation

1. For a fixed station, group each side from its farthest end in blocks of at most `M`.
2. The left leaders are indices `0, M, 2M, ...`; the right leaders are `N-1, N-1-M, ...`.
3. Sweep stations left to right, maintaining the left leader count and coordinate sum.
4. Compute `left[i] = count * position[i] - sum`.
5. Sweep right to left with the mirrored sequence.
6. Compute `right[i] = sum - count * position[i]`.
7. Minimize `left[i] + right[i]` over all criminal indices.
8. Double that minimum because every trip returns.

Farthest-first groups are optimal because closer criminals can be collected along an already necessary route.
