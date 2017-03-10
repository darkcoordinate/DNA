#!/usr/bin/env python
import sys
import matplotlib.pyplot as plt
with open(sys.argv[1]) as f:
	lines = f.readlines()
n_line = int(lines[0])
il = int(sys.argv[2])
fl = int(lines[1+50+ int(sys.argv[2])])
for i in range(0,n_line):
	linep = lines[i+1].split()
	if(i == il):
		plt.plot([float(linep[2]), float(linep[4])], [i, i], "b-")
	elif(i == fl):
		plt.plot([float(linep[2]), float(linep[4])], [i, i], "g-")
	else:
		plt.plot([float(linep[2]), float(linep[4])],[i, i],"r-")

plt.show()
