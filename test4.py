#!/usr/bin/env python
import sys
import matplotlib.pyplot as plt
with open(sys.argv[1]) as f:
	lines = f.readlines()
for i in range(len(lines)):
	s = lines[i].split()
	plt.plot([float(s[0]), float(s[1])] , [i,i])

plt.show()
