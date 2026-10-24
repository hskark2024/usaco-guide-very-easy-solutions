# Test-case walkthroughs

## Two verticals and three horizontals

At `y=0`, active verticals at `x=2` and `x=5` both lie inside `[0,10]`, adding two. At `y=1`, both lie inside `[1,6]`, adding two more. A high horizontal crosses neither, so the total is four.

## No vertical segments

Every event is a query while the Fenwick tree is empty, so the answer stays zero.

## Negative coordinates

Compression uses sorted order rather than raw array indices, so negative values work exactly like positive values.

## More than two billion crossings

Fifty thousand full-width horizontals and fifty thousand full-height verticals create `2,500,000,000` crossings. This confirms that the final total must be a 64-bit integer.
