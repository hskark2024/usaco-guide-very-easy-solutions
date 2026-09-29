# Test-case walkthroughs

In the official sample, several subsets reach height ten, but ordering matters. Trying each possible top cow lets the DP find a stable arrangement whose weakest remaining capacity is two.

For one cow of height ten and strength zero, the answer is zero: no weight is above her, so the stack is just barely safe. If the only cow is shorter than the target, the output is `Mark is too tall`. With twenty unit cows of strength twenty, all are required and the bottom cow has one unit of capacity left.
