NAME	=	parser_exe
SRC		=	$(wildcard srcs/*.cpp)
SRC		+=	$(wildcard srcs/commands/*.cpp)
SRC		+=	$(wildcard srcs/utils/*.cpp)
SRC		+=	$(wildcard tests/*.cpp)
OBJ		=	$(SRC:.cpp=.o)
CFLAGS	=	-Wall -Werror -Wextra -std=c++98
INCLUDES = -I./includes
CC		=	c++

%.o:%.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $^ -o $@

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) $^ -o $(NAME)

clean:
	rm -Rf $(OBJ)

fclean: clean
	rm -Rf $(NAME)

re: fclean all