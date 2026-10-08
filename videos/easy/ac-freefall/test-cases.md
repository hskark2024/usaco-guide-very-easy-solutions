# Test-case walkthroughs

For `A=10` and `B=1`, operation counts zero, one, two, and three give approximately `10`, `8.07`, `7.77`, and `8`. Two operations are optimal.

For `A=5` and `B=10`, one operation already spends ten time units, more than the no-operation total of five. The optimum is the left boundary, zero.

For `A=10^18` and `B=100`, the optimum uses many operations and the answer is about `8.7720532145386e12`. This case checks the wide search interval and high-precision arithmetic.
