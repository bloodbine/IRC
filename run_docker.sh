#!/bin/bash

if [ $# != 1 ]; then
	echo "[+] ./run.sh <port>"
	exit 1
fi

if [ $(docker images | head -2 | tail -1 | awk '{print $1}') != "irc" ]; then
	docker build -t irc .
fi

docker run --rm -p$1:$1 -e PORT=$1 -itv $PWD:/irc irc