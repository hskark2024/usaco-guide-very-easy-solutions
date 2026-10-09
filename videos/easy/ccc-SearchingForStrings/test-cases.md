# Test-case walkthroughs

For needle `aab` and haystack `abacabaa`, the length-three windows include `aba` twice and `baa` once. Both have counts two `a` and one `b`, but the repeated `aba` hash is stored once, so the answer is `2`.

For needle `ab` and haystack `baba`, the candidates are `ba`, `ab`, and `ba`. The set contains two ordered strings even though all three windows are permutations.

For needle `abcd` and haystack `abc`, the early length check returns zero without opening an invalid window.
