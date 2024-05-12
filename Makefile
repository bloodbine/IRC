NAME	=	ircserv
SRC		=	$(wildcard srcs/*.cpp)
SRC		+=	$(wildcard srcs/commands/*.cpp)
OBJ		=	$(SRC:.cpp=.o)
CFLAGS	=	-Wall -Werror -Wextra -std=c++98 -g
INCLUDES = -I./includes
CC		=	c++
PORT	?=	6667

%.o:%.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $^ -o $@

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) $^ -o $(NAME)

clean:
	rm -Rf $(OBJ)

fclean: clean
	rm -Rf $(NAME)

linux:
	@echo "[+] IRC server will run in port: " $(PORT)
	./run_docker.sh $(PORT)

re: fclean all