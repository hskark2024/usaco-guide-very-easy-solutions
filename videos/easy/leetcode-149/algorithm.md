# Algorithm derivation

1. Choose an anchor point `i`.
2. For each later point `j`, compute `dx=x[j]-x[i]` and `dy=y[j]-y[i]`.
3. Divide both by `gcd(|dx|,|dy|)`.
4. If `dx<0`, or `dx=0` and `dy<0`, negate both values.
5. Count the resulting pair in a map.
6. The best map count plus one is the best line through this anchor.
7. Maximize over every anchor.

GCD reduction removes scale, and the sign rule removes the choice between the two directions along one line.
