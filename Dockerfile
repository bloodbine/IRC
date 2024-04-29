FROM debian:12

WORKDIR /irc

RUN apt update -y && apt install -y g++ make valgrind
