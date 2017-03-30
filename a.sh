#!/bin/bash
COMPILER=g++
OUT_FILE=com
COM_FILE=test4.cpp
OBJ_FILE=ki2.obj
if $COMPILER -g -std=c++11 $COM_FILE -I ./ -o $OUT_FILE ;then
	./$OUT_FILE $OBJ_FILE
fi
