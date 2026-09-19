# Algorithm derivation

1. Sum all starting water S and all capacities A.
2. Initialize dp[0][0]=0 and every other cell unreachable.
3. For each glass, update chosen count and old capacity downward. A take transition adds its capacity and water.
4. For each k and reachable C,B, maximize min(2C,S+B).
5. Print the doubled optimum divided by two.
