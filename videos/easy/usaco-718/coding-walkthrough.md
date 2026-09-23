# C++ coding walkthrough

1. Detect `nocross.in` while retaining stdin/stdout for local tests.
2. Read the two field orderings into vectors.
3. Allocate two zero-filled DP rows of length `N+1`.
4. Start each current row with the zero-prefix base case.
5. Take the maximum of the up and left values.
6. When `abs(a[i-1]-b[j-1]) <= 4`, try the diagonal plus one.
7. Swap rows after finishing each upper prefix.
8. Print the last value of the completed row.
