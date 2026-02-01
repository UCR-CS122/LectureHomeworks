#!/usr/bin/python3

import sys
import re

section_names = ["end", "size", "start"]

old_sym_name = re.sub(r'[\/\.\-]', '_', sys.argv[1])
new_sym_name = re.match(r".*(image\d+).*", sys.argv[2]).group(1)

with open(sys.argv[2], 'w') as file:
    for sec in section_names:
        file.write("_binary_" + old_sym_name + "_" + sec + " " + new_sym_name + "_" + sec + "\n")
