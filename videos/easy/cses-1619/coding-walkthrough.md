# C++ coding walkthrough

1. Reserve space for exactly `2*N` event pairs.
2. Read each arrival and departure.
3. Push `{arrival,+1}` and `{departure,-1}`.
4. Sort the vector of pairs.
5. Scan with `currently_inside` and `maximum_inside`.
6. Update the maximum after applying every change.
7. Print the maximum as one integer.
