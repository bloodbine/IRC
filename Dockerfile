FROM debian:12

WORKDIR /irc

COPY run_irc_serv.sh .

RUN apt update -y && apt install -y g++ make valgrind

RUN chmod +x /irc/run_irc_serv.sh

CMD ["/irc/run_irc_serv.sh"]