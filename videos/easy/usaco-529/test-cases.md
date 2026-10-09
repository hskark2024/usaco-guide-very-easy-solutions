# Test-case walkthroughs

For source `whatthemomooofun` and forbidden word `moo`, the first detected suffix is removed while the output is being built. Processing continues and the final text is `whatthefun`.

For source `aaaaa` and forbidden word `aa`, each completed pair is popped. One `a` remains.

For source `abccbc` and forbidden word `bc`, deleting the first `bc` joins the surrounding characters. The stack method naturally checks every later suffix without restarting from the beginning.
