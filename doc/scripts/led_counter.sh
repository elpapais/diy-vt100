#!/bin/sh
while [ 1 ]
do

	#0000 = 0
	echo -e -n "\e[0q\a"
	sleep 1
	
	#0001 = 1
	echo -e -n "\e[0;1q\a"
	sleep 1
	
	#0010 = 2
	echo -e -n "\e[0;2q\a"
	sleep 1
	
	#0011 = 3
	echo -e -n "\e[0;2;1q\a"
	sleep 1
	
	#0100 = 4
	echo -e -n "\e[0;3q\a"
	sleep 1
	
	#0101 = 5
	echo -e -n "\e[0;3;1q\a"
	sleep 1
	
	#0110 = 6
	echo -e -n "\e[0;3;2q\a"
	sleep 1
	
	#0111 = 7
	echo -e -n "\e[0;3;2;1q\a"
	sleep 1
	
	#1000 = 8
	echo -e -n "\e[0;4q\a"
	sleep 1
	
	#1001 = 9
	echo -e -n "\e[0;4;1q\a"
	sleep 1
	
	#1010 = A
	echo -e -n "\e[0;4;2q\a"
	sleep 1
	
	#1011 = B
	echo -e -n "\e[0;4;2;1q\a"
	sleep 1
	
	#1100 = C
	echo -e -n "\e[0;4;3q\a"
	sleep 1
	
	#1101 = D
	echo -e -n "\e[0;4;3;1q\a"
	sleep 1
	
	#1110 = E
	echo -e -n "\e[0;4;3;2q\a"
	sleep 1
	
	#1111 = F
	echo -e -n "\e[0;4;3;2;1q\a"
	sleep 1
done
