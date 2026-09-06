# C++ coding walkthrough

1. Implement binary modular exponentiation and an inverse helper.
2. Allocate a frequency array for gift IDs through one million.
3. Read each child's list, store it, and increment each gift's frequency.
4. Scan the stored lists a second time.
5. Sum `request_count[item]` for every gift on the current list.
6. Multiply by the inverse of the current list size and add to the total.
7. Compute `inverse_n` once and multiply the total by it twice.
8. Print the final value modulo `998,244,353`.
