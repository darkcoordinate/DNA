#!/usr/bin/env python

import sys
import matplotlib.pyplot as plt
with open(sys.argv[1]) as f:
	lines = f.readlines()
for i in range(0,50):
	s = lines[i + 1].split()
	plt.plot([float(s[1]),float(s[3])],[float(s[2]) , float(s[4])])

a = len(lines)
for i in range(51,a):
	s = lines[i].split()
	plt.plot([float(s[0])], [float(s[1])], "ob")
plt.show()	
