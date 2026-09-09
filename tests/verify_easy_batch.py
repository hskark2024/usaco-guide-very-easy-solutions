from bisect import insort
from collections import Counter
from fractions import Fraction
from functools import lru_cache
from math import atan2, gcd
from itertools import combinations, permutations, product
from pathlib import Path
import random
import subprocess
import sys


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
    ):
        verifier()
        print(f"passed {verifier.__name__}")
    sys.exit(0)
