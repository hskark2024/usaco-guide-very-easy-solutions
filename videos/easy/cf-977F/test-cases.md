# Test-case walkthroughs

For `3 3 4 7 5 6 8`, the best chain reaches length four at value six: one valid set of indices is `1 3 5 6`. The seven and eight cannot extend that chain at the moments they appear.

For `1 2 3 4 5`, every position is selected. For `10 9 8 7`, no `x-1` appears earlier, so the answer has length one. For `5 5 6 6 7`, either copy of each repeated value may support a valid length-three chain.
