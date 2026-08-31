from pathlib import Path
import subprocess
import sys

root = Path(__file__).resolve().parents[1]
build = root / "tests" / "build"
build.mkdir(exist_ok=True)
failed = []

for src in sorted((root / "solutions").glob("*.cpp")):
    out = build / src.stem
    cmd = ["g++", "-std=c++17", "-O2", "-Wall", "-Wextra", str(src), "-o", str(out)]
    res = subprocess.run(cmd, capture_output=True, text=True)
    if res.returncode != 0:
        failed.append((src.name, res.stderr))
    else:
        print(f"compiled {src.name}")

if failed:
    for name, err in failed:
        print(f"\nFAILED {name}\n{err}", file=sys.stderr)
    sys.exit(1)
