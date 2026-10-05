# Test-case walkthroughs

In the official hierarchy, employees 4 and 5 share employee 3 as their direct boss, so the first answer is 3. Employee 2 belongs to the director's branch while employee 5 belongs below employee 3, so their first meeting is employee 1. The director is already an ancestor of employee 4, making the final answer 1.

On a chain `1 <- 2 <- 3 <- 4`, the answer for employees 2 and 4 is 2. Leveling employee 4 by two steps makes the two endpoints equal and exercises the ancestor shortcut.

On a wide star, every pair of different non-directors has answer 1. This checks the large-to-small scan when both endpoints already have equal depth.
