# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/15 14:15:32 by gacorrei          #+#    #+#              #
#    Updated: 2023/05/15 14:20:29 by gacorrei         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell
SRC		= main.c
CC		= @cc
CFLAGS	= -Wall -Wextra -Werror -g

all:		$(NAME)

$(NAME):	$(SRC)
			$(CC) $(CFLAGS) $(^) -o $(@) -fsanitize=address

clean:
			@rm -f *.o

fclean:		clean
			@rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re