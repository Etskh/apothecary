#!/usr/local/bin/python3
import os

BUILDER_VERSION = '1.0'

PREAMBLE = """/**********************************************************************
 *
 * DO NOT MODIFY!
 *
 *  This is a generated file created with the event builder
 *  version {}
 *********************************************************************/"""

RULE_TEMPLATE = """
{genpath}: {srcpath}
	{command}
"""


def output_gen_header(path, name, content):
    filename = name + '.hpp'
    header_guard = "_INCLUDE_" + filename.upper().replace('.', '_')
    output = "{preamble}\n#ifndef {header_guard}\n#define {header_guard}\n"
    output += '{content}\n'
    output += "#endif // #ifndef {header_guard}"
    output = output.format(
        preamble=PREAMBLE.format(BUILDER_VERSION),
        header_guard=header_guard,
        content=content
    )
    filepath = os.path.join(path, filename)
    with open(filepath, 'w') as file:
        file.write(output)


def output_gen_footer(path, name, content):
    filename = name + '.cpp'
    output = "{preamble}\n{content}".format(
        preamble=PREAMBLE.format(BUILDER_VERSION),
        content=content
    )
    filepath = os.path.join(path, filename)
    with open(filepath, 'w') as file:
        file.write(output)

    return filepath


def get_make_rule(path, name, srcpath, command):
    return RULE_TEMPLATE.format(
        genpath=os.path.join(path, name + '.cpp'),
        srcpath=srcpath,
        command=command
    )
