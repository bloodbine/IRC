#!/bin/bash

make && valgrind --leak-check=full ./ircserv 4444 a
if [ $? != 0 ]; then
	make re && valgrind --leak-check=full ./ircserv 4444 a
fi
