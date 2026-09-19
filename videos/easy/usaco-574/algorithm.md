# Algorithm derivation

1. Mark before[0].
2. Scan fullness upward and add A or B inside the first layer. At every reachable value x, seed after[x/2].
3. Scan the after layer upward and add A or B there. Do not add another halving transition.
4. Scan downward from T and return the first value marked in either layer.
