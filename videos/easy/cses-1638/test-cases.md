# Test-case walkthroughs

For the official 4×4 grid, begin with 1 in the top-left. Sweep right along the first row. The trap at row two, column two becomes zero, so counts flow around it. The trap in row three, column four removes routes that would enter there. The bottom-right finally holds 3.

A one-cell open grid has answer 1; a one-cell trapped grid has answer 0. A fully trapped second row proves the answer is 0 regardless of the open cells below it.
