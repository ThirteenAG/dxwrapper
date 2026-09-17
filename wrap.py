#!/usr/bin/env python3
"""
wrap_cpp_only_balanced.py - Uses balanced parentheses matching for reliable wrapping
"""

import re
from pathlib import Path
import sys

SKIP_DIRS = {".git", "build", "bin", "out", "Debug", "Release", "__pycache__"}

def should_skip_dir(p: Path) -> bool:
    return any(part in SKIP_DIRS for part in p.parts)

def find_cpp_files(start: Path):
    for item in start.rglob("*.cpp"):
        if should_skip_dir(item):
            continue
        if item.is_file():
            yield item

def process_file(filepath: Path):
    print(f"→ {filepath}")

    try:
        original_text = filepath.read_text(encoding="utf-8", errors="replace")
    except Exception as e:
        print(f"  → Failed to read: {e}")
        return

    lines = original_text.splitlines(keepends=True)

    already_wrapped = re.compile(r"(SAFE|CALL_AND_HANDLE|CHECK_AND_HANDLE)\s*\(")

    # Balanced parentheses pattern — captures full call including all arguments
    pattern = re.compile(
        r"(\bProxyInterface(?:Ex)?\s*->\s*[A-Za-z0-9_]+\s*\([^()]*?(?:\([^()]*\)[^()]*)*\))",
        re.DOTALL
    )

    changed = 0
    new_lines = []

    for line in lines:
        if already_wrapped.search(line):
            new_lines.append(line)
            continue

        def replacer(m):
            call_part = m.group(1)
            return f"SAFE({call_part})"

        new_line = pattern.sub(replacer, line)
        if new_line != line:
            changed += len(pattern.findall(line))
            new_lines.append(new_line)
        else:
            new_lines.append(line)

    if changed > 0:
        filepath.write_text("".join(new_lines), encoding="utf-8")
        print(f"  → {changed} replacements made (file updated)")
    else:
        print("  → No changes needed")


def main():
    if len(sys.argv) < 2:
        print("Usage: python wrap_cpp_only_balanced.py .   or   src   or   file.cpp")
        sys.exit(1)

    for arg in sys.argv[1:]:
        p = Path(arg).resolve()
        if not p.exists():
            print(f"Not found: {arg}")
            continue

        if p.is_file() and p.suffix.lower() == ".cpp":
            process_file(p)
        elif p.is_dir():
            print(f"Scanning: {p}")
            count = 0
            for cpp in find_cpp_files(p):
                process_file(cpp)
                count += 1
            print(f"Processed {count} .cpp files")
        else:
            print(f"Skipped: {arg}")


if __name__ == "__main__":
    main()