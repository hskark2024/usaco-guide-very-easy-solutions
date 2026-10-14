# C++ coding walkthrough

1. Store position, original index, and direction in a `Robot` struct.
2. Sort structs by position.
3. Keep the answer array in original input order.
4. Run the same logic once for parity zero and once for parity one.
5. Use a vector as the stack of unmatched `R` robots.
6. Record direct-pair answers during the scan.
7. Walk the leftover-left vector forward in pairs.
8. Walk the leftover-right vector backward in pairs.
9. Handle the possible cross-wall pair, then print by original index.
