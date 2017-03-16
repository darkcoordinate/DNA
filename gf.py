#!/usr/bin/env python

import sys
import matplotlib.pyplot as plt
with open(sys.argv[1]) as f:
	lines = f.readlines()
i = sys.argv[2]
a = lines[0].split()
b = lines[1].split()
c = lines[2].split()

plt.plot([a[0],a[2]], [a[1], a[3]])
plt.plot([b[0],b[2]], [b[1], b[3]])
plt.plot([c[0]], [c[1]],"ro")
plt.savefig("data"+str(i)+".png")
