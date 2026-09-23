from bisect import insort
from collections import Counter
from collections import deque
from fractions import Fraction
from functools import lru_cache
from math import atan2, gcd
from itertools import combinations, permutations, product
from pathlib import Path
import random
import subprocess
import sys
import tempfile


ROOT = Path(__file__).resolve().parents[1]
BUILD = ROOT / "tests" / "build"
RNG = random.Random(20260903)


def run(stem: str, input_text: str) -> str:
    result = subprocess.run(
        [str(BUILD / stem)],
        input=input_text,
        capture_output=True,
        text=True,
        check=True,
    )
    return result.stdout


def verify_static_rmq() -> None:
    for _ in range(250):
        n = RNG.randint(1, 35)
        q = RNG.randint(1, 80)
        values = [RNG.randint(0, 100) for _ in range(n)]
        queries = []
        expected = []
        for _ in range(q):
            left = RNG.randrange(n)
            right = RNG.randint(left + 1, n)
            queries.append((left, right))
            expected.append(min(values[left:right]))
        input_text = (
            f"{n} {q}\n"
            + " ".join(map(str, values))
            + "\n"
            + "".join(f"{left} {right}\n" for left, right in queries)
        )
        actual = list(map(int, run("ys-StaticRMQ", input_text).split()))
        assert actual == expected


def verify_angle_sort() -> None:
    for _ in range(250):
        n = RNG.randint(1, 60)
        points = [
            (RNG.randint(-25, 25), RNG.randint(-25, 25)) for _ in range(n)
        ]
        input_text = f"{n}\n" + "".join(f"{x} {y}\n" for x, y in points)
        tokens = list(map(int, run("ys-SortPointsByArgument", input_text).split()))
        actual = list(zip(tokens[::2], tokens[1::2]))
        assert Counter(actual) == Counter(points)
        angles = [0.0 if point == (0, 0) else atan2(point[1], point[0]) for point in actual]
        assert all(a <= b + 1e-12 for a, b in zip(angles, angles[1:]))


def verify_depq() -> None:
    for _ in range(250):
        initial = sorted(RNG.randint(-30, 30) for _ in range(RNG.randint(0, 25)))
        model = initial.copy()
        operations = []
        expected = []
        for _ in range(RNG.randint(1, 100)):
            if not model or RNG.random() < 0.55:
                value = RNG.randint(-30, 30)
                operations.append(f"0 {value}")
                insort(model, value)
            elif RNG.random() < 0.5:
                operations.append("1")
                expected.append(model.pop(0))
            else:
                operations.append("2")
                expected.append(model.pop())
        input_text = (
            f"{len(initial)} {len(operations)}\n"
            + (" ".join(map(str, initial)) + "\n" if initial else "\n")
            + "\n".join(operations)
            + "\n"
        )
        actual = list(map(int, run("ys-DEPQ", input_text).split()))
        assert actual == expected


def verify_binomial_coefficients() -> None:
    queries = [(a, b) for a in range(31) for b in range(a + 1)]
    input_text = str(len(queries)) + "\n" + "".join(
        f"{a} {b}\n" for a, b in queries
    )
    actual = list(map(int, run("cses-1079", input_text).split()))

    expected = []
    for a, b in queries:
        row = [1]
        for _ in range(a):
            row = [1] + [row[i - 1] + row[i] for i in range(1, len(row))] + [1]
        expected.append(row[b])
    assert actual == expected


def verify_distributing_apples() -> None:
    def enumerate_distributions(children: int, apples: int) -> int:
        return sum(
            sum(shares) == apples
            for shares in product(range(apples + 1), repeat=children)
        )

    for children in range(1, 6):
        for apples in range(1, 7):
            actual = int(run("cses-1716", f"{children} {apples}\n"))
            assert actual == enumerate_distributions(children, apples)


def verify_candy_lottery() -> None:
    for children in range(1, 5):
        for maximum in range(1, 7):
            outcomes = list(product(range(1, maximum + 1), repeat=children))
            expected = sum(max(outcome) for outcome in outcomes) / len(outcomes)
            actual = float(run("cses-1727", f"{children} {maximum}\n"))
            assert abs(actual - expected) <= 0.5e-6 + 1e-12


def verify_creating_strings_ii() -> None:
    # These short cases cover one copy, all-equal letters, all-distinct
    # letters, and several independent repeated-frequency groups.
    for letters in ("a", "aaaa", "abcd", "aabb", "aabac", "aabbcc", "aaabbc"):
        expected = len(set(permutations(letters)))
        actual = int(run("cses-1715", letters + "\n"))
        assert actual == expected


def verify_almost_identity_permutations() -> None:
    # Exhaustively generate the entire permutation space for small n. This
    # independently checks the subtle requirement that selected moved slots
    # must form a derangement instead of an arbitrary permutation.
    for n in range(4, 9):
        mismatch_histogram = [0] * (n + 1)
        for permutation in permutations(range(n)):
            mismatches = sum(value != index for index, value in enumerate(permutation))
            mismatch_histogram[mismatches] += 1

        for k in range(1, 5):
            expected = sum(mismatch_histogram[: k + 1])
            actual = int(run("cf-888D", f"{n} {k}\n"))
            assert actual == expected


def verify_close_tuples() -> None:
    # Direct combination enumeration is slow on large arrays but is an ideal
    # oracle for these deterministic small random cases.
    for _ in range(300):
        n = RNG.randint(1, 10)
        tuple_size = RNG.randint(1, n)
        allowed_difference = RNG.randint(1, n)
        values = [RNG.randint(1, n) for _ in range(n)]

        expected = 0
        for picked_indices in combinations(range(n), tuple_size):
            picked_values = [values[index] for index in picked_indices]
            expected += max(picked_values) - min(picked_values) <= allowed_difference

        input_text = (
            f"1\n{n} {tuple_size} {allowed_difference}\n"
            + " ".join(map(str, values))
            + "\n"
        )
        actual = int(run("cf-1462E2", input_text))
        assert actual == expected


def verify_exponentiation_ii() -> None:
    modulus = 1_000_000_007

    # Small exact towers form an independent oracle: Python constructs b^c
    # first, while the C++ solution must reduce that exponent safely.
    queries = [
        (a, b, c)
        for a in range(8)
        for b in range(6)
        for c in range(6)
    ]
    input_text = str(len(queries)) + "\n" + "".join(
        f"{a} {b} {c}\n" for a, b, c in queries
    )
    actual = list(map(int, run("cses-1712", input_text).split()))
    expected = [pow(a, pow(b, c), modulus) for a, b, c in queries]
    assert actual == expected


def verify_santas_bot() -> None:
    modulus = 998_244_353

    for _ in range(250):
        child_count = RNG.randint(1, 7)
        lists = []
        for _ in range(child_count):
            item_count = RNG.randint(1, 6)
            lists.append(RNG.sample(range(1, 9), item_count))

        # Enumerate the three random decisions directly as rational numbers.
        # Each valid (x, y, z) path has probability 1/(n*k_x*n).
        probability = Fraction(0, 1)
        wanted_sets = [set(items) for items in lists]
        for first_child, items in enumerate(lists):
            for item in items:
                for recipient in range(child_count):
                    if item in wanted_sets[recipient]:
                        probability += Fraction(
                            1, child_count * len(lists[first_child]) * child_count
                        )

        expected = (
            probability.numerator
            * pow(probability.denominator, modulus - 2, modulus)
            % modulus
        )
        input_text = str(child_count) + "\n" + "".join(
            f"{len(items)} {' '.join(map(str, items))}\n" for items in lists
        )
        actual = int(run("cf-1279D", input_text))
        assert actual == expected


def verify_and_array() -> None:
    modulus = 1_000_000_007

    def compute_and_array(values: list[int]) -> list[int]:
        result = []
        for length in range(1, len(values) + 1):
            total = 0
            for selected in combinations(values, length):
                current = selected[0]
                for value in selected[1:]:
                    current &= value
                total = (total + current) % modulus
            result.append(total)
        return result

    cases = []
    for _ in range(180):
        n = RNG.randint(1, 8)
        cases.append([RNG.randrange(1 << 7) for _ in range(n)])

    encoded_cases = [compute_and_array(values) for values in cases]
    input_text = str(len(cases)) + "\n" + "".join(
        f"{len(values)}\n{' '.join(map(str, encoded))}\n"
        for values, encoded in zip(cases, encoded_cases)
    )

    output_lines = run("cf-2211D", input_text).strip().splitlines()
    assert len(output_lines) == len(cases)
    for source, expected_b, line in zip(cases, encoded_cases, output_lines):
        reconstructed = list(map(int, line.split()))
        assert len(reconstructed) == len(source)
        assert all(0 <= value < (1 << 29) for value in reconstructed)
        assert compute_and_array(reconstructed) == expected_b


def verify_exponentiation() -> None:
    modulus = 1_000_000_007
    queries = [(a, b) for a in range(13) for b in range(18)]
    queries += [
        (0, 0),
        (0, 1_000_000_000),
        (1_000_000_000, 1_000_000_000),
        (999_999_937, 987_654_321),
    ]
    input_text = str(len(queries)) + "\n" + "".join(
        f"{base} {exponent}\n" for base, exponent in queries
    )
    actual = list(map(int, run("cses-1095", input_text).split()))
    expected = [pow(base, exponent, modulus) for base, exponent in queries]
    assert actual == expected


def verify_counting_divisors() -> None:
    values = list(range(1, 2001))
    input_text = str(len(values)) + "\n" + "\n".join(map(str, values)) + "\n"
    actual = list(map(int, run("cses-1713", input_text).split()))
    expected = [
        sum(value % divisor == 0 for divisor in range(1, value + 1))
        for value in values
    ]
    assert actual == expected


def verify_div_game() -> None:
    def prime_powers_up_to(limit: int) -> list[int]:
        powers = []
        for prime in range(2, limit + 1):
            if any(
                prime % divisor == 0
                for divisor in range(2, int(prime**0.5) + 1)
            ):
                continue
            power = prime
            while power <= limit:
                powers.append(power)
                power *= prime
        return powers

    for original in range(1, 81):
        possible_powers = prime_powers_up_to(original)

        @lru_cache(maxsize=None)
        def brute(current: int, used_mask: int) -> int:
            best = 0
            for index, power in enumerate(possible_powers):
                if used_mask & (1 << index) or current % power != 0:
                    continue
                best = max(
                    best,
                    1 + brute(current // power, used_mask | (1 << index)),
                )
            return best

        actual = int(run("ac-DivGame", f"{original}\n"))
        assert actual == brute(original, 0)


def verify_product_one_modulo_n() -> None:
    for modulus in range(2, 101):
        output = list(map(int, run("cf-1514C", f"{modulus}\n").split()))
        printed_size = output[0]
        selected = output[1:]

        assert printed_size == len(selected)
        assert selected == sorted(set(selected))
        assert all(1 <= value < modulus for value in selected)

        product_modulo_n = 1
        for value in selected:
            product_modulo_n = product_modulo_n * value % modulus
        assert product_modulo_n == 1

        units = [
            value
            for value in range(1, modulus)
            if __import__("math").gcd(value, modulus) == 1
        ]
        all_units_product = 1
        for value in units:
            all_units_product = all_units_product * value % modulus
        expected_size = len(units) - (all_units_product != 1)
        assert printed_size == expected_size

        # For tiny moduli, independently enumerate every subset and prove no
        # larger valid selection exists.
        if modulus <= 12:
            brute_best = 0
            for mask in range(1 << (modulus - 1)):
                product = 1
                picked = 0
                for offset in range(modulus - 1):
                    if mask & (1 << offset):
                        product = product * (offset + 1) % modulus
                        picked += 1
                if product == 1:
                    brute_best = max(brute_best, picked)
            assert printed_size == brute_best


def verify_power_products() -> None:
    def is_perfect_kth_power(value: int, power: int) -> bool:
        candidate = 1
        while candidate**power < value:
            candidate += 1
        return candidate**power == value

    for _ in range(350):
        size = RNG.randint(2, 12)
        power = RNG.randint(2, 6)
        values = [RNG.randint(1, 50) for _ in range(size)]
        expected = sum(
            is_perfect_kth_power(values[left] * values[right], power)
            for left in range(size)
            for right in range(left + 1, size)
        )
        input_text = f"{size} {power}\n" + " ".join(map(str, values)) + "\n"
        actual = int(run("cf-1225D", input_text))
        assert actual == expected


def verify_diluc_and_kaeya() -> None:
    def same_ratio(left: str, right: str) -> bool:
        left_d = left.count("D")
        left_k = len(left) - left_d
        right_d = right.count("D")
        right_k = len(right) - right_d
        return left_d * right_k == left_k * right_d

    def brute_prefix(prefix: str) -> int:
        if len(prefix) == 1:
            return 1
        best = 1
        for cuts in range(1 << (len(prefix) - 1)):
            pieces = []
            start = 0
            for index in range(len(prefix) - 1):
                if cuts & (1 << index):
                    pieces.append(prefix[start : index + 1])
                    start = index + 1
            pieces.append(prefix[start:])
            if all(same_ratio(pieces[0], piece) for piece in pieces[1:]):
                best = max(best, len(pieces))
        return best

    cases = [
        "".join(RNG.choice("DK") for _ in range(RNG.randint(1, 10)))
        for _ in range(220)
    ]
    input_text = str(len(cases)) + "\n" + "".join(
        f"{len(case)}\n{case}\n" for case in cases
    )
    output_lines = run("cf-1536C", input_text).strip().splitlines()
    assert len(output_lines) == len(cases)
    for case, output_line in zip(cases, output_lines):
        actual = list(map(int, output_line.split()))
        expected = [brute_prefix(case[:end]) for end in range(1, len(case) + 1)]
        assert actual == expected


def verify_euler_totient() -> None:
    # GCD enumeration is deliberately independent of the sieve formula used by
    # the solution.  It checks every candidate for each small n directly.
    values = list(range(1, 501))
    input_text = str(len(values)) + "\n" + "\n".join(map(str, values)) + "\n"
    actual = list(map(int, run("spoj-etm", input_text).split()))
    expected = [
        sum(gcd(candidate, value) == 1 for candidate in range(1, value + 1))
        for value in values
    ]
    assert actual == expected


def verify_permutation_rounds() -> None:
    def first_reset_round(permutation: list[int]) -> int:
        # Move each labeled element according to the permutation until the full
        # arrangement returns.  This simulates the statement rather than using
        # cycle lengths or an LCM, which makes it a useful independent oracle.
        positions = list(range(len(permutation)))
        rounds = 0
        while True:
            positions = [permutation[position] for position in positions]
            rounds += 1
            if positions == list(range(len(permutation))):
                return rounds

    for size in range(1, 9):
        cases = []
        if size <= 7:
            # Full enumeration is affordable through seven positions.
            cases.extend(permutations(range(size)))
        else:
            # Eight factorial cases would dominate the suite, so use a fixed
            # random sample plus identity and one full cycle.
            cases.extend([tuple(range(size)), tuple(range(1, size)) + (0,)])
            for _ in range(300):
                values = list(range(size))
                RNG.shuffle(values)
                cases.append(tuple(values))

        for permutation in cases:
            input_text = (
                f"{size}\n"
                + " ".join(str(destination + 1) for destination in permutation)
                + "\n"
            )
            actual = int(run("cses-3398", input_text))
            assert actual == first_reset_round(list(permutation))


def verify_playing_with_gcd() -> None:
    limits = list(range(0, 181))
    input_text = str(len(limits)) + "\n" + "\n".join(map(str, limits)) + "\n"
    output_lines = run("spoj-najpwg", input_text).strip().splitlines()
    assert len(output_lines) == len(limits)

    for case_number, (limit, line) in enumerate(zip(limits, output_lines), 1):
        expected = sum(
            gcd(left, right) > 1
            for right in range(1, limit + 1)
            for left in range(1, right + 1)
        )
        assert line == f"Case {case_number}: {expected}"


def verify_frog_one() -> None:
    def enumerate_routes(heights: list[int]) -> int:
        # Enumerate both legal next jumps recursively.  Unlike the submitted
        # bottom-up recurrence, this oracle explores complete routes directly.
        @lru_cache(maxsize=None)
        def brute(stone: int) -> int:
            if stone == len(heights) - 1:
                return 0
            answers = []
            for jump in (1, 2):
                destination = stone + jump
                if destination < len(heights):
                    answers.append(
                        abs(heights[stone] - heights[destination])
                        + brute(destination)
                    )
            return min(answers)

        return brute(0)

    cases = [
        [10, 10],
        [10, 100, 10],
        [10, 30, 40, 20],
        [30, 10, 60, 10, 60, 50],
    ]
    for _ in range(240):
        size = RNG.randint(2, 14)
        cases.append([RNG.randint(1, 50) for _ in range(size)])

    for heights in cases:
        input_text = f"{len(heights)}\n{' '.join(map(str, heights))}\n"
        actual = int(run("ac-frog1", input_text))
        assert actual == enumerate_routes(heights)


def verify_mortal_kombat_tower() -> None:
    def enumerate_sessions(bosses: list[int]) -> int:
        # Recursive enumeration independently tries every sequence of session
        # sizes.  The Boolean says whether the friend owns the next session.
        @lru_cache(maxsize=None)
        def brute(defeated: int, friend_turn: bool) -> int:
            if defeated == len(bosses):
                return 0
            best = len(bosses) + 1
            for take in (1, 2):
                if defeated + take > len(bosses):
                    continue
                cost = sum(bosses[defeated : defeated + take]) if friend_turn else 0
                best = min(best, cost + brute(defeated + take, not friend_turn))
            return best

        return brute(0, True)

    cases = [[0], [1], [1, 1, 1, 1, 1, 1], [1, 0, 1, 1, 0, 1, 1, 1]]
    for _ in range(350):
        size = RNG.randint(1, 15)
        cases.append([RNG.randint(0, 1) for _ in range(size)])

    input_text = str(len(cases)) + "\n" + "".join(
        f"{len(case)}\n{' '.join(map(str, case))}\n" for case in cases
    )
    actual = list(map(int, run("cf-1418C", input_text).split()))
    expected = [enumerate_sessions(case) for case in cases]
    assert actual == expected


def verify_increasing_frequency() -> None:
    def enumerate_operations(values: list[int], target: int) -> int:
        # Only shifts that map some present value to the target can improve the
        # count; k = 0 preserves the baseline.  Exhaust every such shift and
        # every nonempty segment for an independent small-case oracle.
        shifts = {0, *(target - value for value in values)}
        best = values.count(target)
        for left in range(len(values)):
            for right in range(left, len(values)):
                for shift in shifts:
                    candidate = sum(
                        value + shift * (left <= index <= right) == target
                        for index, value in enumerate(values)
                    )
                    best = max(best, candidate)
        return best

    cases = [
        ([9, 9, 9, 9, 9, 9], 9),
        ([6, 2, 6], 2),
        ([1, 5, 5, 1], 5),
        ([2, 7, 7, 2], 4),
    ]
    for _ in range(260):
        size = RNG.randint(1, 10)
        target = RNG.randint(1, 6)
        cases.append(([RNG.randint(1, 6) for _ in range(size)], target))

    for values, target in cases:
        input_text = f"{len(values)} {target}\n{' '.join(map(str, values))}\n"
        actual = int(run("cf-1082E", input_text))
        assert actual == enumerate_operations(values, target)


def verify_hoof_paper_scissors_gold() -> None:
    def score_plan(opponent: list[int], bessie: tuple[int, ...]) -> int:
        # With H=0, P=1, S=2, Bessie's gesture wins exactly when it is one
        # cyclic step ahead of Farmer John's gesture.
        return sum((mine - theirs) % 3 == 1 for mine, theirs in zip(bessie, opponent))

    def brute_match(opponent: list[int], switch_limit: int) -> int:
        # Enumerating every gesture string is intentionally independent of the
        # submitted DP.  It directly filters plans by their adjacent changes.
        best = 0
        for bessie in product(range(3), repeat=len(opponent)):
            switches = sum(
                bessie[index] != bessie[index - 1]
                for index in range(1, len(bessie))
            )
            if switches <= switch_limit:
                best = max(best, score_plan(opponent, bessie))
        return best

    cases = [
        ([1, 1, 0, 1, 2], 1),
        ([0], 0),
        ([0, 1, 2, 0], 0),
        ([0, 1, 2, 0], 3),
    ]
    for _ in range(180):
        size = RNG.randint(1, 8)
        cases.append(
            ([RNG.randrange(3) for _ in range(size)], RNG.randint(0, min(4, size - 1)))
        )

    gesture_text = "HPS"
    for opponent, switch_limit in cases:
        input_text = (
            f"{len(opponent)} {switch_limit}\n"
            + "".join(f"{gesture_text[gesture]}\n" for gesture in opponent)
        )
        actual = int(run("usaco-694", input_text))
        assert actual == brute_match(opponent, switch_limit)


def verify_time_is_mooney() -> None:
    def exact_day_oracle(
        city_count: int,
        roads: list[tuple[int, int]],
        rewards: list[int],
        coefficient: int,
    ) -> int:
        # Random rewards are at most 6 and C is at least 1.  Thus every route
        # longer than day 6 has upper bound 6*t-t^2 <= 0, so checking through
        # day 7 covers every possible positive answer for this oracle domain.
        unreachable = -10**9
        dp = [[unreachable] * city_count for _ in range(8)]
        dp[0][0] = 0
        answer = 0
        for day in range(1, 8):
            for start, destination in roads:
                if dp[day - 1][start] != unreachable:
                    dp[day][destination] = max(
                        dp[day][destination],
                        dp[day - 1][start] + rewards[destination],
                    )
            if dp[day][0] != unreachable:
                answer = max(answer, dp[day][0] - coefficient * day * day)
        return answer

    cases = [
        (3, [(0, 1), (1, 2), (2, 0)], [0, 10, 20], 1, 24),
        (2, [(0, 1)], [0, 6], 1, 0),
        (2, [(0, 1), (1, 0)], [0, 1], 10, 0),
    ]

    for city_count, roads, rewards, coefficient, expected in cases:
        input_text = (
            f"{city_count} {len(roads)} {coefficient}\n"
            + " ".join(map(str, rewards))
            + "\n"
            + "".join(f"{start + 1} {destination + 1}\n" for start, destination in roads)
        )
        assert int(run("usaco-993", input_text)) == expected

    for _ in range(260):
        city_count = RNG.randint(2, 6)
        rewards = [0] + [RNG.randint(0, 6) for _ in range(city_count - 1)]
        coefficient = RNG.randint(1, 5)
        roads = [
            (start, destination)
            for start in range(city_count)
            for destination in range(city_count)
            if start != destination and RNG.random() < 0.34
        ]
        if not roads:
            roads.append((0, 1))

        input_text = (
            f"{city_count} {len(roads)} {coefficient}\n"
            + " ".join(map(str, rewards))
            + "\n"
            + "".join(f"{start + 1} {destination + 1}\n" for start, destination in roads)
        )
        actual = int(run("usaco-993", input_text))
        expected = exact_day_oracle(city_count, roads, rewards, coefficient)
        assert actual == expected


def verify_coin_combinations_one() -> None:
    def enumerate_sequences(coins: tuple[int, ...], remaining: int) -> int:
        # This oracle literally branches on the next coin in the sequence.
        # It does not share the executable's bottom-up table or loop ordering.
        if remaining == 0:
            return 1
        return sum(
            enumerate_sequences(coins, remaining - coin)
            for coin in coins
            if coin <= remaining
        )

    cases = [
        ((2, 3, 5), 9),
        ((1, 2), 4),
        ((4, 6), 5),
        ((3,), 12),
    ]
    for _ in range(240):
        coin_count = RNG.randint(1, 5)
        coins = tuple(sorted(RNG.sample(range(1, 9), coin_count)))
        target = RNG.randint(1, 14)
        cases.append((coins, target))

    for coins, target in cases:
        input_text = f"{len(coins)} {target}\n{' '.join(map(str, coins))}\n"
        actual = int(run("cses-1635", input_text))
        expected = enumerate_sequences(coins, target)
        assert actual == expected


def verify_coin_combinations_two() -> None:
    def enumerate_coin_counts(coins: tuple[int, ...], target: int) -> int:
        # A Cartesian product over copy counts represents every multiset once,
        # independently of the solution's incremental dynamic programming.
        choices = [range(target // coin + 1) for coin in coins]
        return sum(
            sum(count * coin for count, coin in zip(counts, coins)) == target
            for counts in product(*choices)
        )

    cases = [
        ((2, 3, 5), 9),
        ((1, 2), 4),
        ((4, 6), 5),
        ((3, 10), 9),
    ]
    for _ in range(240):
        coin_count = RNG.randint(1, 5)
        coins = tuple(sorted(RNG.sample(range(1, 9), coin_count)))
        target = RNG.randint(1, 18)
        cases.append((coins, target))

    for coins, target in cases:
        input_text = f"{len(coins)} {target}\n{' '.join(map(str, coins))}\n"
        actual = int(run("cses-1636", input_text))
        expected = enumerate_coin_counts(coins, target)
        assert actual == expected


def verify_subset_sum_queries() -> None:
    # Enumerate physical-ball subsets after each valid query. Equal values
    # retain separate positions, matching the judge's distinguishability.
    modulus = 998_244_353
    for _ in range(250):
        target = RNG.randint(1, 15)
        balls = []
        queries = []
        expected = []
        for _ in range(RNG.randint(15, 45)):
            if balls and (len(balls) >= 10 or RNG.random() < 0.45):
                index = RNG.randrange(len(balls))
                value = balls.pop(index)
                queries.append(f"- {value}")
            else:
                value = RNG.randint(1, 20)
                balls.append(value)
                queries.append(f"+ {value}")
            expected.append(sum(
                sum(value for index, value in enumerate(balls) if mask >> index & 1)
                == target
                for mask in range(1 << len(balls))
            ) % modulus)
        input_text = f"{len(queries)} {target}\n" + "\n".join(queries) + "\n"
        actual = list(map(int, run("ac-subsetSumQueries", input_text).split()))
        assert actual == expected

    # Large duplicate multiplicities force modular wraparound in both
    # addition and subtraction. The oracle uses exact binomial coefficients.
    from math import comb
    target = 35
    queries = ["+ 1"] * 80 + ["- 1"] * 80
    counts = list(range(1, 81)) + list(range(79, -1, -1))
    expected = [comb(count, target) % modulus if count >= target else 0 for count in counts]
    actual = list(map(int, run(
        "ac-subsetSumQueries", f"{len(queries)} {target}\n" + "\n".join(queries) + "\n"
    ).split()))
    assert actual == expected


def verify_book_shop() -> None:
    cases = [([4, 8, 5, 3], [5, 12, 8, 1], 10), ([6], [100], 5),
             ([2], [7], 6), ([3, 3, 3], [4, 8, 5], 6)]
    for _ in range(300):
        n = RNG.randint(1, 12)
        cases.append(([RNG.randint(1, 15) for _ in range(n)],
                      [RNG.randint(1, 30) for _ in range(n)], RNG.randint(1, 35)))
    for prices, pages, budget in cases:
        # Enumerating sets of book indices does not use a knapsack recurrence.
        expected = max(
            sum(pages[i] for i in range(len(prices)) if mask >> i & 1)
            for mask in range(1 << len(prices))
            if sum(prices[i] for i in range(len(prices)) if mask >> i & 1) <= budget
        )
        input_text = (f"{len(prices)} {budget}\n" + " ".join(map(str, prices))
                      + "\n" + " ".join(map(str, pages)) + "\n")
        assert int(run("cses-1158", input_text)) == expected


def verify_money_sums() -> None:
    cases = [[4, 2, 5, 2], [7], [2, 2, 2], [1, 2, 4, 8], [5, 10]]
    for _ in range(300):
        cases.append([RNG.randint(1, 20) for _ in range(RNG.randint(1, 12))])
    for coins in cases:
        expected = sorted({
            sum(value for i, value in enumerate(coins) if mask >> i & 1)
            for mask in range(1, 1 << len(coins))
        })
        tokens = list(map(int, run(
            "cses-1745", f"{len(coins)}\n" + " ".join(map(str, coins)) + "\n"
        ).split()))
        assert tokens[0] == len(expected)
        assert tokens[1:] == expected



def verify_two_sets_ii() -> None:
    modulus = 1_000_000_007
    for n in range(1, 21):
        total = n * (n + 1) // 2
        # Enumerate subsets of ALL numbers, then pair each subset with its
        # complement. This oracle does not use the solution's pinned-N DP.
        sums = [0]
        for value in range(1, n + 1):
            sums += [subtotal + value for subtotal in sums]
        expected = sums.count(total // 2) // 2 if total % 2 == 0 else 0
        assert int(run("cses-1093", f"{n}\n")) == expected

    for n in (31, 64, 100, 500):
        total = n * (n + 1) // 2
        target = total // 2
        # Separate immutable rows include N, counting both orientations;
        # use a modular inverse to remove the symmetry at the end.
        counts = [1] + [0] * target
        for value in range(1, n + 1):
            previous = counts
            counts = [
                (previous[s] + (previous[s-value] if s >= value else 0)) % modulus
                for s in range(target + 1)
            ]
        expected = counts[target] * pow(2, modulus - 2, modulus) % modulus
        assert int(run("cses-1093", f"{n}\n")) == expected


def verify_values_you_can_make() -> None:
    cases = [([2, 3], 5), ([25, 25, 50], 50), ([1, 500], 1),
             ([5], 5), ([1, 1, 1], 2), ([5, 6, 1, 10, 12, 2], 18)]
    for _ in range(160):
        coins = [RNG.randint(1, 12) for _ in range(RNG.randint(1, 9))]
        # Select one nonempty subset to ensure a legal payable target.
        mask = RNG.randint(1, (1 << len(coins)) - 1)
        target = sum(v for i, v in enumerate(coins) if mask >> i & 1)
        cases.append((coins, target))

    for coins, target in cases:
        expected = set()
        # Explicit ternary roles: unused, payment-only, payment-and-marked.
        # Enumerating complete assignments is independent of bitset DP.
        for roles in product(range(3), repeat=len(coins)):
            payment = sum(v for v, role in zip(coins, roles) if role != 0)
            if payment == target:
                expected.add(sum(v for v, role in zip(coins, roles) if role == 2))
        tokens = list(map(int, run(
            "cf-687C", f"{len(coins)} {target}\n" + " ".join(map(str, coins)) + "\n"
        ).split()))
        assert tokens == [len(expected)] + sorted(expected)

    for coins, expected in (([1] * 500, list(range(501))),
                            ([500] * 500, [0, 500])):
        tokens = list(map(int, run(
            "cf-687C", "500 500\n" + " ".join(map(str, coins)) + "\n"
        ).split()))
        assert tokens == [len(expected)] + expected


def verify_glass_half_spilled() -> None:
    cases = [[(6, 5), (6, 5), (10, 2)], [(1, 0)], [(1, 1)],
             [(10, 0), (1, 1)], [(1, 1), (1, 1)],
             [(100, 0)] * 4, [(3, 3)] * 5]
    # All legal one- and two-glass cases up to capacity three.
    glasses = [(a, b) for a in range(1, 4) for b in range(a + 1)]
    cases.extend([list(pair) for pair in product(glasses, repeat=2)])
    for _ in range(180):
        capacities = [RNG.randint(1, 12) for _ in range(RNG.randint(1, 10))]
        cases.append([(a, RNG.randint(0, a)) for a in capacities])
    for items in cases:
        n = len(items)
        total = sum(b for a, b in items)
        expected = [Fraction(0) for _ in range(n)]
        # Explicitly enumerate selections; no count/capacity DP compression.
        for mask in range(1, 1 << n):
            chosen = [items[i] for i in range(n) if mask >> i & 1]
            capacity = sum(a for a, b in chosen)
            water = sum(b for a, b in chosen)
            retained = min(Fraction(capacity), Fraction(total + water, 2))
            expected[len(chosen) - 1] = max(expected[len(chosen) - 1], retained)
        actual = list(map(float, run('cf-1458B', str(n) + '\n' + ''.join(
            f'{a} {b}\n' for a, b in items)).split()))
        assert len(actual) == n
        assert all(abs(a - float(e)) < 1e-9 for a, e in zip(actual, expected))
        assert all(a <= b for a, b in zip(actual, actual[1:]))
        assert actual[-1] == total
    # Max N and max total capacity: exact closed-form uniform answers.
    for b in (0, 37, 100):
        actual = list(map(float, run('cf-1458B', '100\n' + f'100 {b}\n' * 100).split()))
        assert actual == [min(100 * k, (100 * b + k * b) / 2) for k in range(1, 101)]


def verify_fruit_feast() -> None:
    def bfs(limit, a, b):
        # Queue traversal explores the original legal moves, in arbitrary
        # order, including the downward water edge; independent of two passes.
        seen = {(0, False)}
        pending = deque(seen)
        while pending:
            fullness, drank = pending.popleft()
            moves = [(fullness + a, drank), (fullness + b, drank)]
            if not drank: moves.append((fullness // 2, True))
            for state in moves:
                if state[0] <= limit and state not in seen:
                    seen.add(state)
                    pending.append(state)
        return max(f for f, drank in seen)
    cases = [(t, a, b) for t in range(1, 13)
             for a in range(1, t + 1) for b in range(1, t + 1)]
    cases += [(8, 5, 6), (15, 10, 10), (10, 7, 7), (1, 1, 1)]
    for _ in range(160):
        t = RNG.randint(1, 180)
        cases.append((t, RNG.randint(1, t), RNG.randint(1, t)))
    for t, a, b in cases:
        assert int(run('usaco-574', f'{t} {a} {b}\n')) == bfs(t, a, b)
    # Large fruit sizes keep a direct enumeration oracle small at maximum T.
    for t, a, b in [(5000000, 1111111, 2222223), (5000000, 1, 5000000)]:
        if a == 1:
            expected = t
        else:
            plain = {i*a + j*b for i in range(t//a + 1)
                     for j in range(t//b + 1) if i*a + j*b <= t}
            expected = max(plain)
            for seed in plain:
                for extra in plain:
                    if seed//2 + extra <= t:
                        expected = max(expected, seed//2 + extra)
        assert int(run('usaco-574', f'{t} {a} {b}\n')) == expected
    # Also exercise the required feast.in/feast.out interface in isolation.
    with tempfile.TemporaryDirectory() as folder:
        path = Path(folder)
        (path / 'feast.in').write_text('8 5 6\n')
        subprocess.run([str(BUILD / 'usaco-574')], cwd=folder, check=True)
        assert (path / 'feast.out').read_text() == '8\n'


def verify_grid_paths() -> None:
    def enumerate_routes(grid):
        n = len(grid)
        if grid[0][0] == '*' or grid[-1][-1] == '*':
            return 0
        # Choose which of the 2n-2 steps are downward. This enumerates routes
        # directly instead of repeating the submitted cell recurrence.
        total = 0
        for down_steps in combinations(range(2 * n - 2), n - 1):
            down_steps = set(down_steps)
            row = column = 0
            legal = True
            for step in range(2 * n - 2):
                if step in down_steps:
                    row += 1
                else:
                    column += 1
                if grid[row][column] == '*':
                    legal = False
                    break
            total += legal
        return total

    cases = [['.'], ['*'], ['..', '..'], ['.*', '..'],
             ['...', '***', '...'], ['....', '.*..', '...*', '*...']]
    for _ in range(220):
        n = RNG.randint(1, 7)
        cases.append([
            ''.join('*' if RNG.random() < 0.30 else '.' for _ in range(n))
            for _ in range(n)
        ])
    for grid in cases:
        expected = enumerate_routes(grid) % 1_000_000_007
        actual = int(run('cses-1638', str(len(grid)) + '\n' + '\n'.join(grid) + '\n'))
        assert actual == expected

    # Exercise all one million cells without requiring a large integer oracle:
    # a fully trapped second row makes the destination unreachable.
    n = 1000
    grid = ['.' * n, '*' * n] + ['.' * n] * (n - 2)
    assert int(run('cses-1638', f'{n}\n' + '\n'.join(grid) + '\n')) == 0


def verify_array_description() -> None:
    modulus = 1_000_000_007

    def enumerate_arrays(description, maximum):
        return sum(
            all(given == 0 or given == value
                for given, value in zip(description, candidate))
            and all(abs(left - right) <= 1
                    for left, right in zip(candidate, candidate[1:]))
            for candidate in product(range(1, maximum + 1), repeat=len(description))
        ) % modulus

    cases = [([0], 1), ([0], 5), ([2, 0, 2], 5), ([1, 3], 3),
             ([0, 0, 0], 2), ([1, 1, 1, 1], 1)]
    for _ in range(260):
        n = RNG.randint(1, 7)
        maximum = RNG.randint(1, 5)
        description = [
            0 if RNG.random() < 0.55 else RNG.randint(1, maximum)
            for _ in range(n)
        ]
        cases.append((description, maximum))
    for description, maximum in cases:
        expected = enumerate_arrays(description, maximum)
        actual = int(run(
            'cses-1746',
            f'{len(description)} {maximum}\n' + ' '.join(map(str, description)) + '\n',
        ))
        assert actual == expected

    # Maximum n and m with a unique fixed array checks bounds and runtime.
    n, maximum = 100_000, 100
    fixed = ' '.join(['50'] * n)
    assert int(run('cses-1746', f'{n} {maximum}\n{fixed}\n')) == 1


def verify_edit_distance() -> None:
    alphabet = 'ABC'

    def graph_distance(source, target):
        # Breadth-first search treats whole strings as graph vertices. It uses
        # the allowed edits themselves, not the prefix-table recurrence.
        max_length = max(len(source), len(target)) + 1
        pending = deque([(source, 0)])
        seen = {source}
        while pending:
            text, distance = pending.popleft()
            if text == target:
                return distance
            neighbors = set()
            for index in range(len(text)):
                neighbors.add(text[:index] + text[index + 1:])
                for letter in alphabet:
                    neighbors.add(text[:index] + letter + text[index + 1:])
            if len(text) < max_length:
                for index in range(len(text) + 1):
                    for letter in alphabet:
                        neighbors.add(text[:index] + letter + text[index:])
            for neighbor in neighbors:
                if len(neighbor) <= max_length and neighbor not in seen:
                    seen.add(neighbor)
                    pending.append((neighbor, distance + 1))
        raise AssertionError('target should always be reachable')

    known_cases = [('A', 'A', 0), ('A', 'B', 1), ('AB', 'A', 1),
                   ('A', 'AB', 1), ('LOVE', 'MOVIE', 2),
                   ('AAAA', 'BBBB', 4), ('ABCA', 'CABA', 2)]
    for first, second, expected in known_cases:
        assert int(run('cses-1639', f'{first}\n{second}\n')) == expected
        assert int(run('cses-1639', f'{second}\n{first}\n')) == expected

    cases = []
    for _ in range(90):
        first = ''.join(RNG.choice(alphabet) for _ in range(RNG.randint(1, 4)))
        second = ''.join(RNG.choice(alphabet) for _ in range(RNG.randint(1, 4)))
        cases.append((first, second))
    for first, second in cases:
        expected = graph_distance(first, second)
        assert int(run('cses-1639', f'{first}\n{second}\n')) == expected
        assert int(run('cses-1639', f'{second}\n{first}\n')) == expected

    # Both dimensions at the maximum; the answer is obvious but forces all
    # 25 million DP cells to be processed.
    first = 'A' * 5000
    second = 'A' * 4999 + 'B'
    assert int(run('cses-1639', f'{first}\n{second}\n')) == 1


def verify_longest_common_subsequence() -> None:
    def is_subsequence(candidate, text):
        position = 0
        for character in text:
            if position < len(candidate) and candidate[position] == character:
                position += 1
        return position == len(candidate)

    def enumerate_subsequences(first, second):
        # Enumerate selections from the shorter input directly.  This oracle
        # does not reuse the solution's prefix-grid recurrence.
        if len(first) > len(second):
            first, second = second, first
        best = 0
        for mask in range(1 << len(first)):
            candidate = ''.join(
                character for index, character in enumerate(first)
                if mask & (1 << index)
            )
            if len(candidate) > best and is_subsequence(candidate, second):
                best = len(candidate)
        return best

    known_cases = [
        ('abcde', 'ace', 3),
        ('abc', 'abc', 3),
        ('abc', 'def', 0),
        ('aaaa', 'aa', 2),
        ('a', 'z', 0),
    ]
    for first, second, expected in known_cases:
        assert int(run('lc-LongestCommonSubsequence', f'{first}\n{second}\n')) == expected
        assert int(run('lc-LongestCommonSubsequence', f'{second}\n{first}\n')) == expected

    alphabet = 'abcd'
    for _ in range(260):
        first = ''.join(RNG.choice(alphabet) for _ in range(RNG.randint(1, 10)))
        second = ''.join(RNG.choice(alphabet) for _ in range(RNG.randint(1, 10)))
        expected = enumerate_subsequences(first, second)
        assert int(run('lc-LongestCommonSubsequence', f'{first}\n{second}\n')) == expected

    # Both official dimensions at their maximum exercise one million cells.
    first = 'a' * 500 + 'b' * 500
    second = 'a' * 500 + 'c' * 500
    assert int(run('lc-LongestCommonSubsequence', f'{first}\n{second}\n')) == 500


def verify_cow_checklist() -> None:
    def distance(first, second):
        return (first[0] - second[0]) ** 2 + (first[1] - second[1]) ** 2

    def enumerate_interleavings(holsteins, guernseys):
        if len(holsteins) == 1:
            route = holsteins + guernseys + holsteins
            return sum(distance(left, right) for left, right in zip(route, route[1:]))

        # Choose the G positions among all middle visits.  H1 and HH are fixed
        # at the ends, while both breed orders are then forced automatically.
        middle_length = len(holsteins) + len(guernseys) - 2
        best = None
        for g_positions in combinations(range(middle_length), len(guernseys)):
            g_positions = set(g_positions)
            route = [holsteins[0]]
            next_h = 1
            next_g = 0
            for position in range(middle_length):
                if position in g_positions:
                    route.append(guernseys[next_g])
                    next_g += 1
                else:
                    route.append(holsteins[next_h])
                    next_h += 1
            route.append(holsteins[-1])
            energy = sum(distance(left, right) for left, right in zip(route, route[1:]))
            best = energy if best is None else min(best, energy)
        return best

    cases = [
        ([(0, 0)], [(3, 4)]),
        ([(0, 0), (2, 0)], [(1, 0)]),
        ([(0, 0), (0, 0)], [(0, 0), (0, 0)]),
        ([(0, 0), (1, 0), (2, 0)], [(0, 3), (1, 3)]),
    ]
    for _ in range(220):
        h = RNG.randint(1, 6)
        g = RNG.randint(1, 5)
        holsteins = [(RNG.randint(0, 8), RNG.randint(0, 8)) for _ in range(h)]
        guernseys = [(RNG.randint(0, 8), RNG.randint(0, 8)) for _ in range(g)]
        cases.append((holsteins, guernseys))

    for holsteins, guernseys in cases:
        expected = enumerate_interleavings(holsteins, guernseys)
        input_text = (
            f'{len(holsteins)} {len(guernseys)}\n'
            + ''.join(f'{x} {y}\n' for x, y in holsteins)
            + ''.join(f'{x} {y}\n' for x, y in guernseys)
        )
        assert int(run('usaco-670', input_text)) == expected

    # Maximum dimensions with coincident coordinates exercise the full table.
    points = '0 0\n' * 2000
    assert int(run('usaco-670', f'1000 1000\n{points}')) == 0

    # Exercise the original file interface in a clean temporary directory.
    with tempfile.TemporaryDirectory() as folder:
        path = Path(folder)
        (path / 'checklist.in').write_text(
            '3 2\n0 0\n1 0\n2 0\n0 3\n1 3\n'
        )
        subprocess.run([str(BUILD / 'usaco-670')], cwd=folder, check=True)
        assert (path / 'checklist.out').read_text() == '20\n'


def verify_radio_contact() -> None:
    deltas = {'N': (0, 1), 'S': (0, -1), 'E': (1, 0), 'W': (-1, 0)}

    def positions(start, path):
        result = [start]
        x, y = start
        for move in path:
            dx, dy = deltas[move]
            x += dx
            y += dy
            result.append((x, y))
        return result

    def enumerate_schedules(farmer_start, bessie_start, farmer_path, bessie_path):
        farmer = positions(farmer_start, farmer_path)
        bessie = positions(bessie_start, bessie_path)
        best = None

        # This recursively lists actual timing schedules.  It is exponential
        # and therefore independent from the polynomial rolling DP program.
        def search(i, j, energy):
            nonlocal best
            if best is not None and energy >= best:
                return
            if i == len(farmer_path) and j == len(bessie_path):
                best = energy if best is None else min(best, energy)
                return
            for move_farmer, move_bessie in ((1, 0), (0, 1), (1, 1)):
                ni, nj = i + move_farmer, j + move_bessie
                if ni > len(farmer_path) or nj > len(bessie_path):
                    continue
                dx = farmer[ni][0] - bessie[nj][0]
                dy = farmer[ni][1] - bessie[nj][1]
                search(ni, nj, energy + dx * dx + dy * dy)

        search(0, 0, 0)
        return best

    cases = [
        ((0, 0), (0, 0), 'N', 'N'),
        ((0, 0), (2, 0), 'E', 'W'),
        ((3, 0), (5, 0), 'NN', 'NWWWWWN'),
        ((4, 4), (0, 0), 'SW', 'NE'),
    ]
    moves = 'NSEW'
    for _ in range(180):
        farmer_path = ''.join(RNG.choice(moves) for _ in range(RNG.randint(1, 5)))
        bessie_path = ''.join(RNG.choice(moves) for _ in range(RNG.randint(1, 5)))
        cases.append((
            (RNG.randint(-5, 5), RNG.randint(-5, 5)),
            (RNG.randint(-5, 5), RNG.randint(-5, 5)),
            farmer_path,
            bessie_path,
        ))

    for farmer_start, bessie_start, farmer_path, bessie_path in cases:
        expected = enumerate_schedules(
            farmer_start, bessie_start, farmer_path, bessie_path
        )
        input_text = (
            f'{len(farmer_path)} {len(bessie_path)}\n'
            f'{farmer_start[0]} {farmer_start[1]}\n'
            f'{bessie_start[0]} {bessie_start[1]}\n'
            f'{farmer_path}\n{bessie_path}\n'
        )
        assert int(run('usaco-598', input_text)) == expected

    # Maximum lengths: they start together and follow the same route, so all
    # diagonal steps cost zero while still filling the full million-cell grid.
    path = 'E' * 1000
    assert int(run('usaco-598', f'1000 1000\n0 0\n0 0\n{path}\n{path}\n')) == 0

    with tempfile.TemporaryDirectory() as folder:
        path = Path(folder)
        (path / 'radio.in').write_text('2 7\n3 0\n5 0\nNN\nNWWWWWN\n')
        subprocess.run([str(BUILD / 'usaco-598')], cwd=folder, check=True)
        assert (path / 'radio.out').read_text() == '28\n'


def verify_no_cross() -> None:
    def enumerate_upper_subsequences(upper, lower):
        # This oracle explicitly lists every subsequence chosen on the upper
        # side.  For one fixed choice, greedily taking the earliest compatible
        # lower endpoint decides whether a noncrossing matching exists.  It is
        # intentionally different from the solution's prefix-grid recurrence.
        best = 0
        for mask in range(1 << len(upper)):
            chosen = [
                upper[index]
                for index in range(len(upper))
                if mask & (1 << index)
            ]
            lower_index = 0
            for breed in chosen:
                while (
                    lower_index < len(lower)
                    and abs(breed - lower[lower_index]) > 4
                ):
                    lower_index += 1
                if lower_index == len(lower):
                    break
                lower_index += 1
            else:
                best = max(best, len(chosen))
        return best

    cases = [
        ([1], [1]),
        ([1], [6]),
        ([1, 2, 3, 4, 5, 6], [6, 5, 4, 3, 2, 1]),
        ([1, 2, 3, 4, 5], [1, 2, 3, 4, 5]),
    ]
    for size in range(1, 9):
        base = list(range(1, size + 1))
        for _ in range(35):
            upper = RNG.sample(base, size)
            lower = RNG.sample(base, size)
            cases.append((upper, lower))

    for upper, lower in cases:
        expected = enumerate_upper_subsequences(upper, lower)
        input_text = (
            f'{len(upper)}\n'
            + ''.join(f'{value}\n' for value in upper)
            + ''.join(f'{value}\n' for value in lower)
        )
        assert int(run('usaco-718', input_text)) == expected

    # The maximum-size identical ordering must match every endpoint while
    # forcing the implementation to fill the complete million-state grid.
    ordering = ''.join(f'{value}\n' for value in range(1, 1001))
    assert int(run('usaco-718', f'1000\n{ordering}{ordering}')) == 1000

    # Exercise the historical USACO file interface in an isolated directory.
    with tempfile.TemporaryDirectory() as folder:
        path = Path(folder)
        (path / 'nocross.in').write_text(
            '6\n1\n2\n3\n4\n5\n6\n6\n5\n4\n3\n2\n1\n'
        )
        subprocess.run([str(BUILD / 'usaco-718')], cwd=folder, check=True)
        assert (path / 'nocross.out').read_text() == '5\n'


def verify_increasing_subsequence() -> None:
    def enumerate_subsequences(values):
        # Enumerating every mask is practical only for tiny arrays, but it is
        # a direct definition-based oracle for the strictly increasing rule.
        best = 0
        for mask in range(1 << len(values)):
            chosen = [
                value for index, value in enumerate(values)
                if mask & (1 << index)
            ]
            if all(left < right for left, right in zip(chosen, chosen[1:])):
                best = max(best, len(chosen))
        return best

    cases = [
        [7, 3, 5, 3, 6, 2, 9, 8],
        [1],
        [4, 4, 4, 4],
        [5, 4, 3, 2, 1],
        [1, 2, 3, 4, 5],
    ]
    for _ in range(260):
        cases.append([RNG.randint(-8, 8) for _ in range(RNG.randint(1, 12))])

    for values in cases:
        expected = enumerate_subsequences(values)
        input_text = f'{len(values)}\n' + ' '.join(map(str, values)) + '\n'
        assert int(run('cses-1145', input_text)) == expected

    increasing = list(range(200000))
    input_text = '200000\n' + ' '.join(map(str, increasing)) + '\n'
    assert int(run('cses-1145', input_text)) == 200000


def verify_towers() -> None:
    @lru_cache(maxsize=None)
    def minimum_tower_count(remaining, tops):
        # Towers are interchangeable, so sorting their exposed tops collapses
        # symmetric states while still trying every legal placement.
        if not remaining:
            return len(tops)
        cube = remaining[0]
        answers = []
        tried_top_values = set()
        for index, top in enumerate(tops):
            if top > cube and top not in tried_top_values:
                tried_top_values.add(top)
                changed = list(tops)
                changed[index] = cube
                answers.append(
                    minimum_tower_count(remaining[1:], tuple(sorted(changed)))
                )
        answers.append(
            minimum_tower_count(remaining[1:], tuple(sorted(tops + (cube,))))
        )
        return min(answers)

    cases = [
        [3, 8, 2, 1, 5],
        [1],
        [4, 4, 4, 4],
        [1, 2, 3, 4, 5],
        [5, 4, 3, 2, 1],
    ]
    for _ in range(220):
        cases.append([RNG.randint(1, 8) for _ in range(RNG.randint(1, 9))])

    for cubes in cases:
        minimum_tower_count.cache_clear()
        expected = minimum_tower_count(tuple(cubes), tuple())
        input_text = f'{len(cubes)}\n' + ' '.join(map(str, cubes)) + '\n'
        assert int(run('cses-1073', input_text)) == expected

    # Equal cubes cannot share a tower, so this also stresses maximum input.
    input_text = '200000\n' + ' '.join(['7'] * 200000) + '\n'
    assert int(run('cses-1073', input_text)) == 200000


if __name__ == "__main__":
    for verifier in (
        verify_static_rmq,
        verify_angle_sort,
        verify_depq,
        verify_binomial_coefficients,
        verify_distributing_apples,
        verify_candy_lottery,
        verify_creating_strings_ii,
        verify_almost_identity_permutations,
        verify_close_tuples,
        verify_exponentiation_ii,
        verify_santas_bot,
        verify_and_array,
        verify_exponentiation,
        verify_counting_divisors,
        verify_div_game,
        verify_product_one_modulo_n,
        verify_power_products,
        verify_diluc_and_kaeya,
        verify_euler_totient,
        verify_permutation_rounds,
        verify_playing_with_gcd,
        verify_frog_one,
        verify_mortal_kombat_tower,
        verify_increasing_frequency,
        verify_hoof_paper_scissors_gold,
        verify_time_is_mooney,
        verify_coin_combinations_one,
        verify_coin_combinations_two,
        verify_subset_sum_queries,
        verify_book_shop,
        verify_money_sums,
        verify_two_sets_ii,
        verify_values_you_can_make,
        verify_glass_half_spilled,
        verify_fruit_feast,
        verify_grid_paths,
        verify_array_description,
        verify_edit_distance,
        verify_longest_common_subsequence,
        verify_cow_checklist,
        verify_radio_contact,
        verify_no_cross,
        verify_increasing_subsequence,
        verify_towers,
    ):
        verifier()
        print(f"passed {verifier.__name__}")
    sys.exit(0)
