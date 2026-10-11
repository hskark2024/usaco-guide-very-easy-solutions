# Test-case walkthroughs

For pattern `01` and target `aaaaaa`, the five positive length splits are `(1,5)` through `(5,1)`. Split `(3,3)` maps both symbols to `aaa`, so four pairs remain.

For pattern `001` and target `kokokokotlin`, the valid pairs are `ko` with `kokotlin`, and `koko` with `tlin`, giving two.

For pattern `010` and target `abcab`, lengths force `r0=ab` and `r1=c`; rebuilding the pattern gives the target exactly.
