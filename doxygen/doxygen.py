import re
import sys

def split_last_space(text):
    text = re.sub(r'^ *', '', text)
    text = re.sub(r' *$', '', text)
    text_split = text.split(' ')
    first = ' '.join(text_split[:-1])
    second = text_split[-1]
    return first, second


def print_doxygen(json_doxy):
    template = '''/**
        @brief BRIEF

PARAMS

        @return 
*/'''
    params = '\n'.join([f'        @param[in] {argument} - {argument}' for argument in json_doxy['arguments']])
    ret = re.sub(r'BRIEF', json_doxy['function_name'], template)
    ret = re.sub(r'PARAMS', params, ret)
    return ret

def insert_doxygen(filename):
    with open(filename) as file:
        lines = []
        for line in file:
            lines.append(line)
        for i, line in enumerate(lines):
            if '/// INSERT_DOXYGEN' in line:
                json_doxy = {}
                index = i+1
                while not ')' in lines[index]:
                   index += 1
                merged_line = re.sub(r'\n', ' ', ''.join(lines[i+1:index+1]))
                # handle constructor:
                merged_line = merged_line.split(')')[0]
                print(merged_line)
                split_sig = merged_line.split('(')
                print(split_sig)
                return_type, function_name = split_last_space(split_sig[0])
                json_doxy['return_type'] = return_type
                json_doxy['function_name'] = function_name
                arguments = {}
                print(split_sig)
                if split_sig[1]:
                    split_args = split_sig[1].split(',')
                    for arg in split_args:
                        arg_type, arg_name = split_last_space(arg)
                        arguments[arg_name] = arg_type
                json_doxy['arguments'] = arguments
                print(f'/// {json_doxy}')
                print(print_doxygen(json_doxy))
            else:
                print(re.sub(r'\n', '', line))


if __name__ == '__main__':
    insert_doxygen(sys.argv[1])

