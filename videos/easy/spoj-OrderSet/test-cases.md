# Test-case walkthroughs

## Duplicate insertion

Insert negative one twice. The set still contains one copy, so its Fenwick position remains one.

## Strict count

With values negative one and two present, `C 0` returns one. A stored value equal to the query would not be counted.

## Valid and invalid ranks

`K 2` returns two. After deleting negative one, `K 1` still returns two, while `K 2` prints `invalid`.

## Extreme values

Negative and positive one billion compress normally because only relative order matters.
