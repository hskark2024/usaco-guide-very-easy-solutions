# Storyboard and slide outline

Voice: Daniel, a male macOS system voice. Calm, clear explanations for a 9th-grade audience. Each narration paragraph corresponds to the matching slide.

## Slide 1: Glass Half Spilled

On screen: Choose exactly k glasses; Transfers lose half the poured water; Codeforces 1458B — USACO Guide Easy.

Visual direction: Show chosen glasses inside a box, outside water crossing a 50% loss gate, and the count-capacity DP grid. Emphasize the terms used in this section and reveal the bullets in reading order.

## Slide 2: Compress a chosen set

On screen: C = its total capacity; B = water already inside it; S = total water everywhere.

Visual direction: Show chosen glasses inside a box, outside water crossing a 50% loss gate, and the count-capacity DP grid. Emphasize the terms used in this section and reveal the bullets in reading order.

## Slide 3: Derive the formula

On screen: Keep B for free; Half of outside water S-B can arrive; Answer = min(C, (S+B)/2).

Visual direction: Show chosen glasses inside a box, outside water crossing a 50% loss gate, and the count-capacity DP grid. Emphasize the terms used in this section and reveal the bullets in reading order.

## Slide 4: What DP must remember

On screen: Exactly k chosen glasses; Combined capacity C; Largest possible starting water B.

Visual direction: Show chosen glasses inside a box, outside water crossing a 50% loss gate, and the count-capacity DP grid. Emphasize the terms used in this section and reveal the bullets in reading order.

## Slide 5: 0/1 knapsack update

On screen: Skip keeps the old state; Take adds capacity and water; Loop count and capacity downward.

Visual direction: Show chosen glasses inside a box, outside water crossing a 50% loss gate, and the count-capacity DP grid. Emphasize the terms used in this section and reveal the bullets in reading order.

## Slide 6: Walk through the sample

On screen: S = 12 total water; k=1: capacity 10, inside 2 gives 7; k=2: first two glasses give 11.

Visual direction: Show chosen glasses inside a box, outside water crossing a 50% loss gate, and the count-capacity DP grid. Emphasize the terms used in this section and reveal the bullets in reading order.

## Slide 7: Edges and precision

On screen: Empty water is a valid state; Answers may end in one half; Double values until final printing.

Visual direction: Show chosen glasses inside a box, outside water crossing a 50% loss gate, and the count-capacity DP grid. Emphasize the terms used in this section and reveal the bullets in reading order.

## Slide 8: C++ and checks

On screen: O(N squared times sum of capacities); Subset enumeration verifies small inputs; Maximum N and capacity are tested.

Visual direction: Show chosen glasses inside a box, outside water crossing a 50% loss gate, and the count-capacity DP grid. Emphasize the terms used in this section and reveal the bullets in reading order.
