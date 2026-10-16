# Test-case walkthroughs

For `N=10, K=10`, every color must receive exactly one marble, so the answer is one. The formula agrees: `C(9,9)=1`.

For `N=30, K=7`, reserve seven marbles and distribute the other 23. Choosing six separators among 29 positions gives `C(29,6)=475020`.

For `K=1`, the only distribution gives every marble to that color, and `C(N-1,0)=1`.

Random cases are checked against Python's arbitrary-precision `math.comb`, including symmetric choices and inputs whose multiply-before-divide intermediate exceeds 64 bits.
