#!/usr/bin/env python3

import sys

def get_matrix():
    matrix = []
    for line in sys.stdin:
        sanitized_line = line.strip()
        if sanitized_line != "{" and sanitized_line != "}":
            matrix.append(sanitized_line)
    return matrix

def get_pretty_hex(num):
    pretty_hex = hex(num)
    pretty_hex = pretty_hex[2:len(pretty_hex)]
    return pretty_hex.upper()

def get_top_row_comment(row_length):
    space = " " * 2
    indent = " " * 8
    disp = indent + "/* "
    for i in range(row_length):
        disp += get_pretty_hex(i) + space
    disp += "*/"
    return disp

def get_beginning_of_col_comment(num):
    return "/* " + get_pretty_hex(num) + " */"

def print_row(row_num, row_data):
    print(get_beginning_of_col_comment(row_num), end="    ")
    for cell in row_data:
        print(cell, end=" ")
    print()

def prettify_matrix(matrix, row_length):
    print("{")
    print(get_top_row_comment(row_length))
    for i in range(int(len(matrix) / row_length)):
        offset = i * row_length
        print_row(i, matrix[offset:offset + row_length])
    print("}")
	    


def main():
    prettify_matrix(get_matrix(), 16)

if __name__ == "__main__":
    main()
