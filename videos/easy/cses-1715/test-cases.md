# Test-case walkthroughs

## Official example: `aabac`

The string has five letters with frequencies `a=3`, `b=1`, and `c=1`. The formula gives `5! / (3!1!1!) = 120/6 = 20` distinct strings.

## All letters equal: `aaaa`

All `4!` labeled orders look like the same visible string. The formula is `4!/4! = 1`.

## All letters different: `abcd`

Every order is visibly different, so the denominator is `1` and the result is `4! = 24`.

## Two repeated pairs: `aabb`

The count is `4!/(2!2!) = 6`. Listing `aabb`, `abab`, `abba`, `baab`, `baba`, and `bbaa` confirms it.
