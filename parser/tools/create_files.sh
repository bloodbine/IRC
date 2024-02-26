#!/bin/bash

: '
This is a tool for automating the creation of objects and tests.
It receives 2 arguments. The first argument is for the type of file creation,
either object or test. The second is the name of the object or function to create and test.
ex:
[+] ./create_files.sh 1 ObjName
[+] ./create_files.sh 2 functionName
'

if [ "$#" -eq "2" ] && [ "$1" -eq "1" ]; then
	echo "Build Obj"
elif [ "$#" -eq "2" ] && [ "$1" -eq "2" ]; then
	# create the test file file
	echo "#include \"parserTest.hpp\"" > ../tests/test_$2.cpp
	echo "" >> ../tests/test_$2.cpp
	echo "void	test_$2() {" >> ../tests/test_$2.cpp
	echo -e "\t" >> ../tests/test_$2.cpp
	echo "}" >> ../tests/test_$2.cpp
	# create the function file
	echo "#include \"parser.hpp\"" > ../srcs/$2.cpp
else
	echo "Invalid number of args"
	echo "[+] ./create_files.sh [option] [name]"
fi
