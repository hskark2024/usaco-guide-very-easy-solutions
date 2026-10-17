# Test-case walkthroughs

With labels `3,4,3,6` and edges `1->2`, `1->3`, `2->4`, `3->4`, all four edges count. Only `1->3->4` has values `3,3,6`, so the total is five.

With two vertices labeled `10,10` and both directed edges present, each edge is valid but neither can continue to value 20. The answer is two.

Equal-valued destination vertices deliberately share one map key, while their separate edges still add separate path counts.

The independent checker enumerates every simple path for small random graphs and compares the exact recurrence result.
