#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys
import matplotlib.pyplot as plt
import random as r
with open(sys.argv[1]) as f:
	lines = f.readlines()

k = int(lines[0])
lef = []
for i in range(k):
	ki = lines[i+1].split();
	f = '%06x' % r.randrange(0xffffff)
	plt.plot([float(ki[0]), float(ki[2])],[float(ki[1]), float(ki[3])], color="#"+f, label="foejo"+str(i))
ni = len(lines) - k
for i in range(ni - 1):
	ki = lines[k+ i + 1].split()
	print ki
	plt.plot([float(ki[0])], [float(ki[1])],"o")
plt.legend()
plt.show()
