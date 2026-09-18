# Storyboard and slide outline

Voice: Daniel, a male macOS system voice. Calm, clear, conversational explanations for a 9th-grade audience. Each numbered narration paragraph corresponds to the matching slide. The simple local renderer spaces slides evenly over the narration; reviewers can adjust timing before publishing.

## Slide 1: The Values You Can Make

On screen: Choose coins paying exactly K; Find totals inside some valid payment; Codeforces 687C — USACO Guide Easy.

Visual direction: Draw a grid with payment total along the vertical axis and marked-inside total along the horizontal axis. The origin is lit. A coin v has three possible arrows from each lit cell: stay put when unused, move down by v when included only in the payment, or move diagonally down-right by v when also marked. Shade the row for payment K; its lit columns are the answer. For coins 2 and 3 with K=5, the highlighted row contains inside sums 0,2,3,5. Animate rows from K downward so the current coin cannot travel twice.

## Slide 2: Two totals, one state

On screen: payment = total coins handed over; inside = total coins marked within payment; Start at (0,0).

Visual direction: Highlight only the quantities introduced in this section. Reveal bullets in reading order; use the detailed visualization in the problem notes for a richer edit.

## Slide 3: A coin has three roles

On screen: Unused: keep the old state; Payment only: add v to payment; Payment and inside: add v to both.

Visual direction: Highlight only the quantities introduced in this section. Reveal bullets in reading order; use the detailed visualization in the problem notes for a richer edit.

## Slide 4: A bitset row

On screen: possible[p] holds all inside sums for p; Unmarked coin copies source bits; Marked coin shifts source bits left by v.

Visual direction: Highlight only the quantities introduced in this section. Reveal bullets in reading order; use the detailed visualization in the problem notes for a richer edit.

## Slide 5: Update rows downward

On screen: Read possible[p-v] before this coin; Merge source OR shifted source; Each physical coin is used at most once.

Visual direction: Highlight only the quantities introduced in this section. Reveal bullets in reading order; use the detailed visualization in the problem notes for a richer edit.

## Slide 6: Trace coins 2 and 3

On screen: For payment K=5, select both coins; Inside subsets: {}, {2}, {3}, {2,3}; Answer: 0, 2, 3, 5.

Visual direction: Highlight only the quantities introduced in this section. Reveal bullets in reading order; use the detailed visualization in the problem notes for a richer edit.

## Slide 7: Official samples and edges

On screen: 25,25,50 with K=50: 0,25,50; 0 and K are always valid if payment exists; Skip coins above K; preserve duplicates.

Visual direction: Highlight only the quantities introduced in this section. Reveal bullets in reading order; use the detailed visualization in the problem notes for a richer edit.

## Slide 8: C++ and verification

On screen: K+1 rows of bitset<501>; Output set bits in row K in ascending order; Ternary brute force and maximum-size checks.

Visual direction: Highlight only the quantities introduced in this section. Reveal bullets in reading order; use the detailed visualization in the problem notes for a richer edit.
