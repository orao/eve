#!/usr/bin/env python3.9

import argparse
import pathlib

import constants

from compilation_driver import run_compilation, compilation_arguments


def parse_options():
    parser = argparse.ArgumentParser(
        description='''
Part of assembly approval testing.
Generates asm for sources in 'test/asm/sources'.
You can optionally supply specific source instead of all.
You can also specify architectures (by default will compile all availiable ones).
Compiler used: $CXX
Extra options can be passed through: $CXX_OPTIONS
''',
        formatter_class=argparse.RawTextHelpFormatter)
    parser.add_argument('--output_dir', type=str, required=False,
                        default=str(constants.EXPECTED_DIR))
    compilation_arguments(parser)
    return parser.parse_args()


def write_compiled_results(where, compiled):
    dir_path = pathlib.Path(where)
    pathlib.Path(dir_path).mkdir(parents=True, exist_ok=True)

    for file, contents in compiled.items():
        with open(dir_path.joinpath(file), 'w') as f:
            f.write(contents)


def main():
    options = parse_options()
    compiled = run_compilation(options)
    write_compiled_results(options.output_dir, compiled)


if __name__ == '__main__':
    main()
