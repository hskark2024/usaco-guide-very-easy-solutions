# Storyboard and slide outline

Voice: Daniel, a male macOS system voice. Calm, clear, conversational explanations for a 9th-grade audience. Each numbered narration paragraph corresponds to the matching slide. The simple local renderer spaces slides evenly over the narration; reviewers can adjust timing before publishing.

## Slide 1: Two Sets II

On screen: Split 1 through N into equal sums; Count each unordered split once; CSES 1093 — Easy in USACO Guide.

Visual direction: Draw numbers 1 through N as cards beside two equal-size sum bars. Pin card N to the right group. The left group must fill a bar of height N(N+1)/4 using cards 1 through N-1. Beneath it, draw a row of exact-sum counters. For each card v, highlight arrows from sum s-v to sum s while sweeping from right to left. Use a different color for keeping a card out versus placing it in the left group. With N=3, pin 3 right and highlight the single left selection {1,2}.

## Slide 2: Can a split exist?

On screen: Total = N(N+1)/2; An odd total cannot split equally; Otherwise target = total/2.

Visual direction: Highlight only the quantities introduced in this section. Reveal bullets in reading order; use the detailed visualization in the problem notes for a richer edit.

## Slide 3: Choose one representative

On screen: Pin N to the right group; Build the left group from 1 through N-1; Every partition has exactly one side without N.

Visual direction: Highlight only the quantities introduced in this section. Reveal bullets in reading order; use the detailed visualization in the problem notes for a richer edit.

## Slide 4: Exact-sum counting

On screen: ways[s] counts subsets totaling s; Start ways[0] = 1; Skip v or include v: ways[s] += ways[s-v].

Visual direction: Highlight only the quantities introduced in this section. Reveal bullets in reading order; use the detailed visualization in the problem notes for a richer edit.

## Slide 5: Why scan downward?

On screen: Read states before this number; Each number appears at most once; Reduce every addition modulo 1,000,000,007.

Visual direction: Highlight only the quantities introduced in this section. Reveal bullets in reading order; use the detailed visualization in the problem notes for a richer edit.

## Slide 6: Trace N = 3

On screen: Total 6; target 3; pin 3 right; Use 1 and 2: one subset totals 3; Left {1,2}; right {3}.

Visual direction: Highlight only the quantities introduced in this section. Reveal bullets in reading order; use the detailed visualization in the problem notes for a richer edit.

## Slide 7: Samples and pitfalls

On screen: N=7 gives 4; N=1 gives 0; Do not count both sides separately; Do not divide a modular residue with ordinary /2.

Visual direction: Highlight only the quantities introduced in this section. Reveal bullets in reading order; use the detailed visualization in the problem notes for a richer edit.

## Slide 8: C++ and verification

On screen: Check parity; allocate target+1 counters; Loop values below N and sums downward; O(N³) time, O(N²) space; brute-force verified.

Visual direction: Highlight only the quantities introduced in this section. Reveal bullets in reading order; use the detailed visualization in the problem notes for a richer edit.
