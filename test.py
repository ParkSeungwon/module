#!/usr/bin/python

import sys

with open("/dev/memory") as f:
    print f.read(int(sys.argv[1]));
