#!/bin/bash

make re
valgrind --leak-check=full ./ircserv 4444 a