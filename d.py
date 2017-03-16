#!/usr/bin/env python

import sys
import matplotlib.pyplot as plt
with open(sys.argv[1]) as f:
	lines = f.readlines()

print( len(lines))
