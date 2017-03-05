#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys
import matplotlib.pyplot as plt
with open(sys.argv[1]) as f:
    lines = f.readlines()

bx = []
by = []
for strng in lines:
    k =  strng.split()
    bx.append(float(k[0]))
    by.append(float(k[1]))

plt.plot(bx,by,'r.')
plt.show()