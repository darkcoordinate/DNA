#!/bin/bash
for i in {0..100}
	do
		echo ${i}
		./a.out > kd
		./gf.py kd ${i}
	done
