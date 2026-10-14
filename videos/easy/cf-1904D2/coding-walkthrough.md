# C++ coding walkthrough

1. Define a segment-tree node containing `maximum_original` and `minimum_target`.
2. Combine nodes with `max` for the first field and `min` for the second.
3. Build occurrence vectors while reading the original array.
4. Use `lower_bound` to locate the nearest source on the right.
5. Use its predecessor for the nearest source on the left.
6. Normalize candidate endpoints before the inclusive range query.
7. Test both blocker inequalities inside a small lambda.
8. Stop at the first unsupplied target and print `NO`; otherwise print `YES`.
