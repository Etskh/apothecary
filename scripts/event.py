import os
from . import gensrc

DEFAULT_EVENT_CONTENT = """
# Lifecycle events
init
update
kill

# Input system
input.mousedown
input.mouseup
input.mousemove
input.keydown
input.keyup
input.gamepad.button
input.gamepad.axis

# General app events
app.touch
app.start
app.move
app.action
"""

HEADER_TEMPLATE = """
namespace event {{

enum Type {{
{event_list}
}}; // enum Type

// Declare the etostr function for this type
const char* etostr(event::Type type);

}} // namespace event
"""

FOOTER_TEMPLATE = """
#include "{header_name}"

const char* event::etostr(event::Type type) {{
    static const char* names[] = {{
{event_names}
    }};
    return names[type];
}}
"""


def get_list(filename):
    try:
        with open(filename) as f:
            event_names = f.readlines()
            return [ x.strip() for x in event_names if x.strip() and x.strip()[0] != '#' ]
    except FileNotFoundError:
        with open(filename, 'w') as f:
            f.write(DEFAULT_EVENT_CONTENT)
        return get_list(filename)


def output_header(path, name, events):
    event_list = '\t' + ',\n\t'.join([
        x.upper().replace('.', '_') for x in events
    ])
    content = HEADER_TEMPLATE.format(
        event_list=event_list
    )
    return gensrc.output_gen_header(path, name, content)


def output_footer(path, name, events):
    event_names = '\t\t"' + '",\n\t\t"'.join(events) + '",'
    content = FOOTER_TEMPLATE.format(
        header_name=name + '.hpp',
        event_names=event_names
    )
    return gensrc.output_gen_footer(path, name, content)


def generate():
    path = './src/core'
    event_list_path = './events.md'
    events = get_list(event_list_path)
    name = "_gen_EventTypes"
    output_header(path, name, events)
    output_footer(path, name, events)
    command = 'python3 ' + __name__.replace('.', '/') + '.py'
    return gensrc.get_make_rule(path, name, event_list_path, command)


if __name__ == '__main__':
    generate()
