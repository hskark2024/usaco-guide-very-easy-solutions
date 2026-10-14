# C++ coding walkthrough

1. Flatten `(row,column)` into `row*W+column` to store compact cell IDs.
2. Allocate `vector<vector<int>> bucket(Y+1)`.
3. Use `scheduled[cell]` so boundary corners and later neighbors enter only once.
4. Put the scheduling formula in one lambda.
5. Seed all four borders.
6. Process a bucket with an index, not a range loop, because it may grow.
7. Convert each cell ID back to a row and column.
8. Schedule four valid neighbors using the current year.
9. Print the area after every year's chain reaction finishes.
