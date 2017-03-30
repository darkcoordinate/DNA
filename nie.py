#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys
import matplotlib.pyplot as plt
with open(sys.argv[1]) as f:
	lines = f.readlines()

k = lines[0].split()
plt.plot([float(k[0]), float(k[2])],[float(k[1]), float(k[3])], "r")
n = int(lines[1])
#for i in range(n):
#	k = lines[2+i].split()
#	plt.plot([float(k[0]), float(k[2])],[float(k[1]), float(k[2])],"b")
n2 = int(lines[n+2])
for i in range(n2):
	print i+n+3
	k = lines[2+n+ 1+ i].split()
	plt.plot([float(k[0]), float(k[2])],[float(k[1]), float(k[3])],"g")
	if( len(k) > 4):
		plt.plot([float(k[4])],[float(k[5])],"o")
		print(k[4] + " "+ k[5])	
plt.show()
plt.savefig("ps"+sys.argv[2]+".png")
