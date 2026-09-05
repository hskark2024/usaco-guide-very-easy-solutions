# Edge-case checklist

- [x] `m=1` counts every index once.
- [x] Equal values remain separate selectable indices.
- [x] A window with fewer than `m` total elements contributes zero.
- [x] A window containing the whole array uses the correct binomial coefficient.
- [x] The right pointer starts beyond `left` and never moves backward.
- [x] The combination helper rejects impossible `r > n` requests.
- [x] Factorials cover the maximum total test length of 200,000.
- [x] Every sum and product is reduced modulo `1,000,000,007`.
