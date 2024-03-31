
import re

def parse_log_file(log_file):
    log_data = []

    with open(log_file, 'rb') as file:  # Open the file in binary mode
        entry_lines = []
        row = 0
        lines = file.readlines()
        while row < len(lines):
            if lines[row].startswith(b'-*-*-*-*'):
                my_input = lines[row + 1]
                Signature = lines[row+2]
                Errno = lines[row+3]
                row += 3
                if my_input.startswith(b'Input') and Signature.startswith(b'Signature') and Errno.startswith(b'Errno'):
                    new_entry = {'Signature': Signature.split(b":")[1][:-1].decode('utf-8'),
                                 'Input': my_input.split(b":")[1][:-1],
                                 'Errno': int(Errno.split(b":")[1][:-1])
                                 }
                    entry_lines.append(new_entry)
            row += 1
    return entry_lines


if __name__ == "__main__":
    log_file = "Log.txt"
    parsed_data = parse_log_file(log_file)
    print(parsed_data)
    for entry in parsed_data:
        print(entry)
