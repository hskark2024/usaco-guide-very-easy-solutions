# C++ coding walkthrough

1. Read values and the target as `long long`.
2. Write a helper that begins with subset sum zero.
3. For each value, append that value to every previously existing sum.
4. Generate the two half lists.
5. Sort only the right list.
6. Call `equal_range` for each required complement.
7. Add iterator distance to a `long long` answer.
8. Print the count with a newline.
