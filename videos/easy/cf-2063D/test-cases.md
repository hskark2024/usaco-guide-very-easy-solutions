# Test-case walkthroughs

For one lower point at `0` and upper points `-1 0 1`, only one triangle fits. Pairing `-1` and `1` gives area `2`.

For lower points `0 100` and upper points `-100 -50 0 50`, one triangle uses the widest upper pair for `150`. With two triangles, one pair must come from each row, so the total is `100 + 100 = 200`.

When each row has six points, up to four triangles may fit because both rows have at least four points and twelve total points supply four groups of three. Extreme coordinates verify that accumulated areas require `long long`.
