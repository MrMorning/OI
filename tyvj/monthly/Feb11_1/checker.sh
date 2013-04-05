#!/bin/bash -e

MAKER="./bridge_datamaker"
PROG1="./bridge_std"
PROG2="./bridge"

cnt=0
while [ 1 ] 
do
	let cnt=$cnt+1
	echo $cnt
	echo $@ $RANDOM | $MAKER
	time $PROG1 > $PROG1.out
	time $PROG2 > $PROG2.out
	head -1 $PROG1.out
	head -1 $PROG2.out
	echo ""
	diff -bc $PROG1.out $PROG2.out
done
