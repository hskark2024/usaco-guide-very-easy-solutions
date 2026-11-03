# Algorithm derivation

A direct query follows too many individual jumps. Divide the row into square-root-sized blocks. For each hole, summarize all jumps until the path first exits its block: next block position, number of jumps, and last visited hole.

Build from right to left because powers are positive. A query consumes one summary per block. An update rebuilds only one block, giving `O(sqrt(N))` work for both operations.
