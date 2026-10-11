# Test-case walkthroughs

In the official sample, A prefix two is `{1,2}` and B prefix three is also `{1,2}` even though `2` occurs twice, so the answer is `Yes`.

If A is `10,20,30` and B begins `20,30`, B has two known ranks with maximum three. Because count and maximum differ, rank one is missing and the prefix is invalid.

If B ever introduces a value absent from all of A, that and every longer B prefix remain invalid.
