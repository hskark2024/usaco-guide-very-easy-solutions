# Test-case walkthroughs

## Official example

The first full-route query chooses the best original shortcut and returns eleven. After checkpoint four moves twice, the later sub-routes use updated edge lengths and savings and both return eight.

## No legal skip

A query with one checkpoint has distance zero. A query with two checkpoints uses their direct edge because neither endpoint may be skipped.

## Collinear detour

If a middle checkpoint lies on a shortest Manhattan route between its neighbors, its saving is zero.

## Large detour

If a middle checkpoint travels far away and back, skipping it creates a large positive saving that the maximum tree must select.
