# Test-case walkthroughs

## `7 5 5 7`

Push `7`, then `5`. Since `7>5`, merge to average `6`. The next `5` still violates `6>5`, so merge again to average `17/3`. The final `7` stays separate. Output three copies of `17/3`, then `7`.

## Already nondecreasing

For `7 8 8 10 12`, no adjacent averages violate the order, so every block remains length one and the original sequence is printed.

## Fully decreasing

For `4 3 2 1`, every push triggers merging until one block remains. All four outputs equal `2.5`.

## Equal neighboring averages

Equal averages do not need to merge. Whether represented as one block or two, they expand to the same correct values.
