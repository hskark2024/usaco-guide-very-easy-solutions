from bisect import insort
from collections import Counter
from math import atan2
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


if __name__ == "__main__":
    for verifier in (verify_static_rmq, verify_angle_sort, verify_depq):
        verifier()
        print(f"passed {verifier.__name__}")
    sys.exit(0)
