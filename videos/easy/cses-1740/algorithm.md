# Algorithm derivation

A vertical segment can cross the current sweep height only after its lower endpoint and before its upper endpoint. Represent those moments as add and remove events. At a horizontal event, count active vertical x-coordinates inside the horizontal range with a Fenwick range sum.

Compress only vertical x-coordinates. Use `lower_bound` for the first compressed x at least the left endpoint and `upper_bound` for the first x beyond the right endpoint. Sorting events and processing each Fenwick operation costs `O(n log n)` total with `O(n)` storage.
