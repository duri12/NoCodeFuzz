import re


def parse_log_file(log_file):
    log_data = []

    with open(log_file, 'rb') as file:  # Open the file in binary mode
        entry_lines = []
        row = 0
        lines = file.readlines()
        while row < len(lines):
            if lines[row].startswith(b'-*-*-*-*'):
                row += 1
                my_input = lines[row]
                if my_input.startswith(b'Input'):
                    row += 1
                    while b'Signature' not in lines[row]:
                        my_input = my_input + lines[row]
                        row += 1

                Signature = lines[row]
                Errno = lines[row + 1]
                row += 1
                if my_input.startswith(b'Input') and Signature.startswith(b'Signature') and Errno.startswith(b'Errno'):
                    new_entry = {
                        'Input': my_input.split(b":")[1][:-1],
                        'Errno': int(Errno.split(b":")[1][:-1]),
                        'Signature': Signature.split(b":")[1][:-1].decode('utf-8')
                    }
                    entry_lines.append(new_entry)
            row += 1
    return entry_lines


if __name__ == "__main__":
    log_file = "Log.txt"
    parsed_data = parse_log_file(log_file)
    for entry in parsed_data:
        print(entry)
