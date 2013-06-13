#!/bin/sh
while [ 1 ]
do
	echo -e -n "\e[0;1q"
	echo -e -n "\a"
	
	sleep 1
	
	echo -e -n "\e[0;2q"
	echo -e -n \\a
	
	sleep 1
	
	echo -e -n "\e[0;3q"
	echo -e -n "\a"
	
	sleep 1
	
	echo -e -n "\e[0;4q" 
	echo -e -n "\a"
	
	sleep 1
	
	echo -e -n "\e[0;3q"
	echo -e -n "\a"
	
	sleep 1
	
	echo -e -n "\e[0;2q"
	echo -e -n \\a
	
	sleep 1
done
