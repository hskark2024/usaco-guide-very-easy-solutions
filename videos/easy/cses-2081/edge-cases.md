# Edge-case checklist

- `N=1`: there are no paths between distinct endpoints.
- `K1=K2`: inclusive endpoints must still work.
- `K1=1`: subtract `atMost(0)`, which contains no distinct pairs.
- `K2=N`: depths may exceed the actual diameter but do no harm.
- Equal endpoint depths use `count choose 2`.
- Prefix range excludes the current depth after equal pairs are handled.
- Same-group pairs are subtracted.
- 200,000-node chain uses iterative component and depth walks.
- The result can be about `N^2/2`, so use 64-bit integers.
