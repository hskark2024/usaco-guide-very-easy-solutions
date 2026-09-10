# Edge-case checklist

- Every value already equals `c`: choose `k = 0` and keep all `N` targets.
- No value equals `c`: convert the most frequent useful value within one segment.
- One array element: the answer is always `1`.
- Targets between equal source values may make restarting better than extending.
- Unrelated values between source occurrences have weight zero and do not hurt a segment.
- The best operation can cover the entire array or a single position.
- Maximum value and `N` fit the allocated tables and linear pass.
