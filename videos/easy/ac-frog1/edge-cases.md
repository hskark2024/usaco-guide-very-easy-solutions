# Edge-case checklist

- `N = 2`: only the one-step jump exists.
- Equal heights: a jump can cost zero.
- A locally cheap jump can lead to an expensive future jump, so greedy choice is unsafe.
- The optimal route may use only one-step jumps, only two-step jumps, or a mixture.
- Maximum `N`: one linear pass fits comfortably.
- Large accumulated cost: `long long` avoids relying on a narrow total-cost bound.
