# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rdragan <rdragan@student.42heilbronn.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/03 14:10:51 by rdragan           #+#    #+#              #
#    Updated: 2024/04/03 14:13:49 by rdragan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	ircserv
SRC		=	$(wildcard srcs/*.cpp)
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