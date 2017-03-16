#!/usr/bin/env python
import sys
import matplotlib.pyplot as plt
with open(sys.argv[1]) as f:
	lines = f.readlines()
n_line = int(lines[0])
il = int(sys.argv[2])
fl = int(lines[1+50+ int(sys.argv[2])])
plt.subplot(2,1,1)
for i in range(0,n_line):
	linep = lines[i+1].split()
	if(i == il):
		plt.plot([float(linep[2]), float(linep[4])], [i, i], "b-")
	elif(i == fl):
		plt.plot([float(linep[2]), float(linep[4])], [i, i], "g-")
	else:
		plt.plot([float(linep[2]), float(linep[4])],[i, i],"r-")

plt.subplot(2,1,2)
ylin = lines[51 + 4*il + 2].split()
klin = len(ylin)
print(klin)
for i in range(0, klin):
	linep = lines[int(ylin[i]) + 1].split()
	linek = lines[51 + 4*il + 3].split()
	plt.plot([float(linek[2]), float(linek[3])],[il, il], "r-")
	print(max(float(linep[3]),float(linep[5])))
	plt.plot([float(linep[3]), float(linep[5])], [i,i], "b-")
plt.show()

