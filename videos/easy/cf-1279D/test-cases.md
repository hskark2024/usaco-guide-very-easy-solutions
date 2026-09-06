# Test-case walkthroughs

## First official example

Lists are `{2,1}` and `{1}`. Gift frequencies are `freq[1]=2` and `freq[2]=1`. The first child's weighted total is `(1+2)/2`; the second's is `2/1`. Multiplying their sum by `1/2^2` gives `7/8`, whose required modular representation is `124780545`.

## One child, one gift

With only one child and one listed gift, every random choice is forced and valid. The answer is `1`.

## Disjoint gift lists

If every child requests a different gift, each chosen gift is accepted by only its original child. The recipient matches with probability `1/n`, regardless of which first child was selected.

## Identical lists

If all children have the same gift list, every chosen gift is accepted by every recipient, so the answer is `1`.

## Uneven list sizes

A gift from a short list must get more probability weight than a gift from a long list. Multiplying each child's frequency sum by `inverse(k_x)` preserves this distinction.
