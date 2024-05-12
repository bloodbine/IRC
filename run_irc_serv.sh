#!/bin/bash

make && valgrind --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./ircserv $PORT test
if [ $? != 0 ]; then
	make re && valgrind --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./ircserv $PORT test
fi
