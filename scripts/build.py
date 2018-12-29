#!/usr/local/bin/python3
import json


FILENAME='build.json'

def get_default_build():
    return {
        'build': 1,
        'version': 1,
    }


def write_info(info):
    with open(FILENAME, 'w') as build:
        json.dump(info, build, indent=2)
    return info


def get_info():
    try:
        with open(FILENAME) as build:
            return json.load(build)
    except FileNotFoundError:
        return write_info(FILENAME, get_default_build())


def increment():
    info = get_info()
    info['build'] += 1
    write_info(info)
    return info


if __name__ == "__main__":
    print(increment())
