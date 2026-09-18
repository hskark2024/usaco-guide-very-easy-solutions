# Edge-case checklist

- [ ] Odd total returns zero before allocation.
- [ ] N=3 is the first valid equal split.
- [ ] Do not include N in the counting DP.
- [ ] ways[0]=1 represents one empty subset.
- [ ] Descending sums prevent reusing a number.
- [ ] Reduce every addition modulo M; ordinary integer division by two is unnecessary.
- [ ] N=500 fits the chosen integer total and DP size.
