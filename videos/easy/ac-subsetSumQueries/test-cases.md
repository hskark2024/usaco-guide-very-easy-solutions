# Test-Case Walkthroughs

## Add then remove

For `K = 5`, add `2`, then `3`. The answers are `0`, then `1` because `{2,3}` reaches five. Removing `2` returns the answer to zero.

## Duplicate values

For `K = 4`, add three separate balls valued `2`. After the second ball there is one subset; after the third there are three choices of which pair to take. Removing one returns the answer to one.

## Value above target

For `K = 4`, adding or removing a ball valued `9` leaves every tracked subset count unchanged.

## Official sample

The 15 queries exercise both directions, repeated fives, and several simultaneous representations. The reported sequence ends at five ways to total ten.
