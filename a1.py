#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys
import matplotlib.pyplot as plt
with open(sys.argv[1]) as f:
	lines = f.readlines()

with open(sys.argv[2]) as f:
	lines2 = f.readlines()
bx = []
by = []
for strng in lines:
	k =  strng.split()
	bx.append(float(k[0]))
	by.append(float(k[1]))
cx = []
cy = []
for strng in lines2:
	k = strng.split();
	cx.append(float(k[0]))
	cy.append(float(k[1]))

plt.plot(cx,cy,'b.')
plt.plot(bx,by,'r.')
plt.show()
