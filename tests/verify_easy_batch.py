from bisect import insort
from collections import Counter
from fractions import Fraction
from math import atan2
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
    ):
        verifier()
        print(f"passed {verifier.__name__}")
    sys.exit(0)
