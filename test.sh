#!/bin/sh


for file in *.txt
do
	i=`echo $file|sed 's/result//g'|sed 's/\.txt//g'`
	echo "test: "$i
	g++ -std=c++14 -Wall -Werror -O2 -o test$i test$i.cpp
	./test$i > out$i.txt
	diff out$i.txt result$i.txt
	rm out$i.txt

done    

