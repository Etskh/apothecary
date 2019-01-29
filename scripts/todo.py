from os import listdir
from os.path import isfile, join


class Task():
    def __init__(self, line_number, phrase, filepath):
        self.line_number = line_number
        self.phrase = phrase[phrase.find(':')+2:].rstrip('\n')
        self.filepath = filepath

    def __str__(self):
        return '{}@{}: {}'.format(
            self.filepath,
            self.line_number,
            self.phrase,
        )

def get_code_files_r(path):
    # Exit if we're in the extern path
    if 'extern' in path:
        return []

    onlyfiles = []
    files = [f for f in listdir(path)]
    for f in files:
        filepath = join(path, f)
        if isfile(filepath):
            onlyfiles.append(filepath)
        else:
            onlyfiles.extend(get_code_files_r(filepath))
    return onlyfiles

def main():
    files = get_code_files_r('./src')

    todos = []
    for filepath in files:
        with open(filepath) as f:
            for num, line in enumerate(f, 1):
                if 'TODO:' in line:
                    todos.append(Task(num, line, filepath))

    for todo in todos:
        print(str(todo))

if __name__ == '__main__':
    main()
