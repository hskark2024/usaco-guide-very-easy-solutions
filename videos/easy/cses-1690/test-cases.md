# Test-case walkthroughs

In the official four-city sample, routes `1,2,3,4` and `1,3,2,4` are both valid, so the answer is two.

With only the flight `1 -> 2`, a two-city graph has one route. Without that flight it has zero. A complete directed graph on `N` cities has `(N-2)!` valid orders for its middle cities. Parallel flights multiply the number of route choices and are kept by the implementation.
