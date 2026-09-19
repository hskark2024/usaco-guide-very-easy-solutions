# Storyboard and slide outline

Voice: Daniel, a male macOS system voice. Calm, clear explanations for a 9th-grade audience. Each narration paragraph corresponds to the matching slide.

## Slide 1: Fruit Feast

On screen: Eat fruit A or fruit B; Drink water at most once; USACO Gold — USACO Guide Easy.

Visual direction: Show two number lines labeled before water and after water, rightward fruit jumps, and one diagonal halving arrow. Emphasize the terms used in this section and reveal the bullets in reading order.

## Slide 2: Why one array is not enough

On screen: A fullness value can occur in two phases; Before water: halving is available; After water: halving is forbidden.

Visual direction: Show two number lines labeled before water and after water, rightward fruit jumps, and one diagonal halving arrow. Emphasize the terms used in this section and reveal the bullets in reading order.

## Slide 3: First reachability layer

On screen: Start at fullness zero; Move right by A or B; Stop every move above T.

Visual direction: Show two number lines labeled before water and after water, rightward fruit jumps, and one diagonal halving arrow. Emphasize the terms used in this section and reveal the bullets in reading order.

## Slide 4: Use the one water move

On screen: From each reachable x; Mark floor(x / 2) after water; Odd fullness rounds down.

Visual direction: Show two number lines labeled before water and after water, rightward fruit jumps, and one diagonal halving arrow. Emphasize the terms used in this section and reveal the bullets in reading order.

## Slide 5: Second reachability layer

On screen: Again move right by A or B; Never halve from this layer; Scan upward for unlimited fruit.

Visual direction: Show two number lines labeled before water and after water, rightward fruit jumps, and one diagonal halving arrow. Emphasize the terms used in this section and reveal the bullets in reading order.

## Slide 6: Walk through T=8

On screen: Reach 5 or 6 before water; Drink at 5 to reach 2; Then eat 6 and finish exactly at 8.

Visual direction: Show two number lines labeled before water and after water, rightward fruit jumps, and one diagonal halving arrow. Emphasize the terms used in this section and reveal the bullets in reading order.

## Slide 7: Edges and implementation

On screen: Water is optional; Byte arrays use about 2(T+1) bytes; USACO files plus stdin fallback.

Visual direction: Show two number lines labeled before water and after water, rightward fruit jumps, and one diagonal halving arrow. Emphasize the terms used in this section and reveal the bullets in reading order.

## Slide 8: Correctness and checks

On screen: Both layers equal all legal histories; O(T) time and O(T) space; BFS oracle and maximum T tests.

Visual direction: Show two number lines labeled before water and after water, rightward fruit jumps, and one diagonal halving arrow. Emphasize the terms used in this section and reveal the bullets in reading order.
