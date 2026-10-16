# Algorithm derivation

1. Read all test cases and record the largest sum `S`.
2. Allocate the triangular Pascal table through row `S`.
3. Set both ends of every row to one modulo `M`.
4. Fill interior cells with the sum of the two parents modulo `M`.
5. For a test case, start `answer=1` and `placed=0`.
6. For each count `c`, set `placed += c` and multiply by `C(placed,c)`.
7. Print the accumulated residue.
