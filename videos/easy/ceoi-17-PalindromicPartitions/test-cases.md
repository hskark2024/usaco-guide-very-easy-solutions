# Test-case walkthroughs

`racecar` can split into seven one-letter chunks. Reading those chunks from either direction gives the same sequence, so seven is optimal.

`deleted` becomes `(d)(e)(let)(e)(d)`, giving five chunks. The greedy scan first matches `d`, then `e`, and leaves `let` as the center.

`racecars` has no equal nonempty prefix and suffix before the center. The entire word must be one center chunk, so the answer is one.
