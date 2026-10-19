# Test-case walkthroughs

## Official example

With prices `8 6 4 5 7 5`, the cheapest delivery to building two costs five. After building five's price becomes one, delivery from there makes the new answer four.

## Customer at an endpoint

At building one only the right formula is needed; at building `n` only the left formula is needed. Including `k` in both ranges remains safe.

## Local pizzeria wins

The pizzeria in the customer's building has zero delivery cost and is evaluated by both formulas.

## Distant pizzeria wins

A low enough base price can beat every nearby source after delivery is added.
