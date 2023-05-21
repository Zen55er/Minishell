# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gacorrei <gacorrei@student.42lisboa.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/15 14:15:32 by gacorrei          #+#    #+#              #
#    Updated: 2023/05/21 08:41:38 by gacorrei         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell
SRC			= main.c lexer.c signals.c utils.c utils_lexer.c utils_lists.c
CC			= @cc
LIBFT		= libft/libft.a
LIBFT_DIR	= libft
CFLAGS		= -Wall -Wextra -Werror -g -lreadline

all:		$(NAME)

$(NAME):	$(SRC)
			@$(MAKE) --no-print-directory -C $(LIBFT_DIR)
			$(CC) $(CFLAGS) $(^) -o $(@) $(LIBFT) -fsanitize=address

clean:
			@$(MAKE) --no-print-directory -C $(LIBFT_DIR) clean

fclean:		clean
			@$(MAKE) --no-print-directory -C $(LIBFT_DIR) fclean
			@rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re