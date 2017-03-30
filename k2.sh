#!/bin/bash
for i in {0..100}
	do
		echo ${i}
		./nie.py line${i}.fl ${i}
	done
