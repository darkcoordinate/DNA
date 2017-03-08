#!/bin/bash
COMPILER=g++
OUT_FILE=com
COM_FILE=test.cpp
OBJ_FILE=sfd.obj
if $COMPILER -g $COM_FILE -I ./ -o $OUT_FILE ;then
	./$OUT_FILE $OBJ_FILE
fi
