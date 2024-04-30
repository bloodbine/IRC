#!/bin/bash

make && valgrind --leak-check=full ./ircserv $PORT a
if [ $? != 0 ]; then
	make re && valgrind --leak-check=full ./ircserv $PORT a
fi
