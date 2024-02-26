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
	# create hpp file
	echo "#pragma once" > ../includes/$2.hpp
	echo "" >> ../includes/$2.hpp
	echo "#include \"parser.hpp\"" >> ../includes/$2.hpp
	echo "" >> ../includes/$2.hpp
	echo "class $2" >> ../includes/$2.hpp
	echo "{" >> ../includes/$2.hpp
	echo "private:" >> ../includes/$2.hpp
	echo "public:" >> ../includes/$2.hpp
	echo -e "\t$2();" >> ../includes/$2.hpp
	echo -e "\t~$2();" >> ../includes/$2.hpp
	echo "};" >> ../includes/$2.hpp
	# create cpp file
	echo "#include \"$2.hpp\"" >> ../srcs/$2.cpp
	echo "" >> ../srcs/$2.cpp
	echo "$2::$2() :" >> ../srcs/$2.cpp
	echo "$2::~$2()" >> ../srcs/$2.cpp

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
	echo "[+] [option 1] => Object creation"
	echo "[+] [option 2] => File and test file creation"
fi
