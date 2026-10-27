# Test-case walkthroughs

## Official sample

The best location reaches the patches with weights `3`, `4`, and `1`, totaling `8`. The weight-`7` patch is too far from that group.

## Exact boundary

Two patches whose transformed coordinate difference is exactly `2K` must remain together. This checks the strict removal condition `difference > 2K` and inclusive `v` update endpoints.

## Random oracle

For small distinct point sets, enumerate every transformed square whose lower boundaries align with point coordinates. Directly sum its weights and compare that maximum with the sweep result.

## Maximum constraints

Place `100,000` distinct patches on one horizontal line, give each weight `10,000`, and choose `K=2,000,000`. Every patch fits, so the expected total is `1,000,000,000`.
