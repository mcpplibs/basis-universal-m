#!/usr/bin/env python3
"""Audit the module surface against the public headers.

src/basis_universal.cppm must be exactly what tools/surface.py writes from
tools/surface.json, and every name of that record must be found in a header
under upstream/basis_universal/transcoder. With a clang++ (--clang, or MWRAP_CLANG) the
record itself is derived again from the headers as the compiler reads them and
must be the same: no public name is left out, none is exported that is not
there. MWRAP_REQUIRE_CLANG=1 makes the second half mandatory (CI's LLVM row).
"""
import argparse
import os
from pathlib import Path
import re
import sys

sys.path.insert(0, str(Path(__file__).resolve().parent))
import surface  # noqa: E402


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--clang', default=os.environ.get('MWRAP_CLANG'))
    args = parser.parse_args()
    record = surface.record()
    written = surface.MODULE.read_text(encoding='utf-8')
    assert written == surface.module_text(record), 'src/basis_universal.cppm is not what tools/surface.py --write gives'
    headers = ''.join(path.read_text(encoding='utf-8', errors='replace') for path in sorted((surface.INCLUDE / 'transcoder').glob('*.h')))
    count = 0
    for namespace, kinds in record.items():
        for kind, names in kinds.items():
            for name in names:
                count += 1
                assert re.search(r'(?<![\w])' + re.escape(name) + r'(?![\w])', headers), f'{namespace}::{name} is in no header'
                if kind == 'internal':
                    assert f'using ::{namespace}::{name};' not in written, f'{namespace}::{name} has internal linkage and is exported'
                    continue
                line = f'inline constexpr auto {name} = ::{namespace}::{name};' if kind == 'adapted' else f'using ::{namespace}::{name};'
                assert line in written, line
    if args.clang:
        derived = surface.derive(args.clang)
        assert derived == record, {namespace: sorted(set(sum(derived.get(namespace, {}).values(), [])) ^ set(sum(record.get(namespace, {}).values(), [])))
                                   for namespace in set(derived) | set(record)}
    else:
        assert os.environ.get('MWRAP_REQUIRE_CLANG') != '1', 'MWRAP_REQUIRE_CLANG=1 and no clang++ given'
    adapted = sum(len(kinds.get('adapted', [])) for kinds in record.values())
    internal = sum(len(kinds.get('internal', [])) for kinds in record.values())
    print(f'{count} names: {count - adapted - internal} exported, {adapted} constants of internal linkage adapted, {internal} of internal linkage left to the header; '
          + ('the record is what clang derives from the headers' if args.clang else 'the record not derived again (no clang++ given)'))


if __name__ == '__main__':
    main()
