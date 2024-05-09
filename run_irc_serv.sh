#!/bin/bash

make && valgrind --leak-check=full --show-leak-kinds=all ./ircserv $PORT a
if [ $? != 0 ]; then
	make re && valgrind --leak-check=full --show-leak-kinds=all ./ircserv $PORT a
fi
