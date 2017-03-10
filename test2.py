#!/usr/bin/env python
import sys
import matplotlib.pyplot as plt
with open(sys.argv[1]) as f:
	lines = f.readlines()
n_line = int(lines[0])
for i in range(0,n_line):
	linep = lines[i+1].split()
	plt.plot([float(linep[2]), float(linep[4])],[i, i],"r-")

plt.show()
