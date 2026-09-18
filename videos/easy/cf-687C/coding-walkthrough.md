# C++ coding walkthrough

Open the [commented solution](../../../solutions/cf-687C.cpp).

1. Read N and K; allocate K+1 bitset<501> rows.

2. Set possible[0][0] to true.

3. Read every coin and skip its transitions if value exceeds K.

4. For payment totals descending, copy the unchanged source row.

5. OR the source and its left shift into the destination.

6. Collect valid bits in row K, then print the count and sorted values.

Compile with `g++ -std=c++17 -O2 -Wall -Wextra`. Run the official samples, then the independent verifier in `tests/verify_easy_batch.py`.
