#!/bin/bash
echo "hello"
if g++ test4.cpp -I ./ -o data ;then
	./data
fi
