#!/bin/sh
while [ 1 ]
do
	echo -e -n "\e[0;1q\a"
	sleep .2
	
	echo -e -n "\e[0;2q\a"
	sleep .2
	
	echo -e -n "\e[0;3q\a"
	sleep .2
	
	echo -e -n "\e[0;4q\a" 
	sleep .2
	
	echo -e -n "\e[0;3q\a"
	sleep .2
	
	echo -e -n "\e[0;2q\a"
	sleep .2
done
