#!/usr/bin/env python3
"""The module's export list, derived from the transcoder's header.

With --clang <clang++> the header is read by the compiler: every name declared
at namespace scope in `basist`, `basisu` and the namespaces inside them by
<transcoder/basisu_transcoder.h> and the headers it includes is recorded in
tools/surface.json, by namespace and kind. src/basis_universal.cppm is written
from that record (--write), one `using` a name: a using-declaration carries
every overload and every template of the name. An unscoped enumeration's
enumerators are names of the namespace too and are exported one by one.

What has internal linkage cannot be exported: every translation unit that
includes the header has its own. A constant of a scalar type (`const uint32_t
COLOR5_PAL0_PREV_HI = 9;`) is recorded as `adapted` and declared again, with
its name, type and value, under `mcpplibs::mwrap::basis_universal::<its
namespace>`. A `static` function, a constant table (an array) and a `const float`
or `const double` that is not `constexpr` (its value is no constant
expression, so it cannot be given again) are recorded as `internal` and are
not in the module: a program that
needs one includes the header (tests/header_mix_test.cpp shows the two used
together).
"""
import argparse
import json
from pathlib import Path
import subprocess
import sys
import tempfile

ROOT = Path(__file__).resolve().parent.parent
INCLUDE = ROOT / 'upstream/basis_universal'
RECORD = ROOT / 'tools/surface.json'
MODULE = ROOT / 'src/basis_universal.cppm'
HEADER = 'transcoder/basisu_transcoder.h'
ROOTS = ('basist', 'basisu')
ADAPTED = 'mcpplibs::mwrap::basis_universal'
TYPES = {'CXXRecordDecl', 'ClassTemplateDecl', 'EnumDecl', 'TypeAliasDecl', 'TypedefDecl', 'TypeAliasTemplateDecl'}
FUNCTIONS = {'FunctionDecl', 'FunctionTemplateDecl'}
# Declarations that name nothing of their own.
PASSED = {'UsingDirectiveDecl', 'UsingDecl', 'UsingShadowDecl', 'ClassTemplateSpecializationDecl', 'ClassTemplatePartialSpecializationDecl',
          'CXXDeductionGuideDecl', 'StaticAssertDecl', 'EmptyDecl', 'CXXMethodDecl', 'CXXConstructorDecl', 'CXXDestructorDecl',
          'CXXConversionDecl', 'FriendDecl', 'LinkageSpecDecl', 'VarTemplateSpecializationDecl', 'VarTemplatePartialSpecializationDecl'}
KINDS = ('types', 'enumerators', 'constants', 'functions', 'adapted', 'internal')


def trees(clang):
    """Every namespace-scope declaration of the translation unit that includes the header."""
    with tempfile.TemporaryDirectory(prefix='basis-surface-') as directory:
        source = Path(directory) / 'all.cpp'
        source.write_text(f'#include <{HEADER}>\n', encoding='utf-8')
        out = []
        for name in ROOTS:
            command = [clang, '-std=c++23', '-fsyntax-only', '-w', '-I', str(INCLUDE), '-Xclang', '-ast-dump=json', '-Xclang', f'-ast-dump-filter={name}', str(source)]
            text = subprocess.run(command, check=True, stdout=subprocess.PIPE, text=True).stdout
            decoder, at = json.JSONDecoder(), 0
            while True:
                while at < len(text) and text[at] != '{':
                    at = text.find('\n', at) + 1 if text.find('\n', at) >= 0 else len(text)
                if at >= len(text):
                    break
                tree, at = decoder.raw_decode(text, at)
                out.append(tree)
        return out


def derive(clang):
    found = {}
    unknown = set()

    def of(scope):
        return found.setdefault(scope, {kind: set() for kind in KINDS})

    def walk(node, scope):
        for child in node.get('inner', []):
            kind, name = child.get('kind'), child.get('name')
            if kind == 'NamespaceDecl':
                assert name, f'a namespace without a name in {scope}'
                walk(child, f'{scope}::{name}' if scope else name)
                continue
            if child.get('isImplicit'):
                continue
            if kind == 'EnumDecl' and 'scopedEnumTag' not in child:
                of(scope)['enumerators'].update(inner['name'] for inner in child.get('inner', []) if inner.get('kind') == 'EnumConstantDecl')
            if not name:
                continue
            if kind in TYPES:
                of(scope)['types'].add(name)
            elif kind in FUNCTIONS:
                of(scope)['internal' if child.get('storageClass') == 'static' else 'functions'].add(name)
            elif kind == 'VarTemplateDecl':
                of(scope)['constants'].add(name)
            elif kind == 'VarDecl':
                kind_of = child.get('type', {}).get('qualType', '')
                if child.get('storageClass') == 'extern' or child.get('inline'):
                    of(scope)['constants'].add(name)
                elif child.get('storageClass') != 'static' and '[' not in kind_of and (
                        child.get('constexpr') or (kind_of.startswith('const ') and 'float' not in kind_of and 'double' not in kind_of)):
                    of(scope)['adapted'].add(name)
                else:
                    of(scope)['internal'].add(name)
            elif kind not in PASSED:
                unknown.add(f'{kind} {scope}::{name}')

    for tree in trees(clang):
        if tree.get('kind') == 'NamespaceDecl' and tree.get('name') in ROOTS:
            walk({'inner': [tree]}, '')
    assert not unknown, sorted(unknown)
    for scope, kinds in found.items():
        both = kinds['functions'] & kinds['internal']
        assert not both, f'{scope}: declared both with and without internal linkage: {sorted(both)}'
        kinds['constants'] -= kinds['adapted'] | kinds['internal']
    return {scope: {kind: sorted(names) for kind, names in kinds.items() if names} for scope, kinds in sorted(found.items()) if any(kinds.values())}


def record():
    return json.loads(RECORD.read_text(encoding='utf-8'))


def module_text(surface=None):
    surface = surface or record()
    lines = ["// mcpplibs.mwrap.basis_universal — Basis Universal's transcoder (KTX2 and .basis textures to pixels or",
             "// to a GPU's own compressed format) as a C++ module. Every exported name is the upstream entity of",
             '// <transcoder/basisu_transcoder.h>, in the namespace upstream declares it in: `basist`, `basisu` and',
             '// the namespaces inside them. Written by tools/surface.py from the header as the compiler reads it',
             '// (tools/surface.json; tools/check_exports.py holds the three together).',
             'module;',
             f'#include <{HEADER}>',
             '',
             'export module mcpplibs.mwrap.basis_universal;',
             '']
    for namespace, kinds in surface.items():
        if not any(kinds.get(kind) for kind in ('types', 'enumerators', 'constants', 'functions')):
            continue
        lines.append(f'export namespace {namespace} {{')
        for kind, title in (('types', 'types'), ('enumerators', 'enumerators of unscoped enumerations'), ('constants', 'objects'), ('functions', 'functions and operators')):
            names = kinds.get(kind, [])
            if names:
                lines.append(f'// {title}')
                lines += [f'using ::{namespace}::{name};' for name in names]
        lines += [f'}}  // namespace {namespace}', '']
    lines += ["// The header's scalar constants of internal linkage (every includer has its own, and none can be",
              '// exported), again under their names with their types and values.']
    for namespace, kinds in surface.items():
        if kinds.get('adapted'):
            lines.append(f'export namespace {ADAPTED}::{namespace} {{')
            lines += [f'inline constexpr auto {name} = ::{namespace}::{name};' for name in kinds['adapted']]
            lines += [f'}}  // namespace {ADAPTED}::{namespace}', '']
    return '\n'.join(lines)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--clang', help='derive tools/surface.json with this clang++')
    parser.add_argument('--write', action='store_true', help='write src/basis_universal.cppm')
    args = parser.parse_args()
    if args.clang:
        RECORD.write_text(json.dumps(derive(args.clang), indent=1) + '\n', encoding='utf-8')
    if args.write:
        MODULE.write_text(module_text(), encoding='utf-8')
    surface = record()
    for namespace, kinds in surface.items():
        print(namespace + ': ' + ', '.join(f'{len(names)} {kind}' for kind, names in kinds.items()))


if __name__ == '__main__':
    sys.exit(main())
