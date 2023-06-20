# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpatrao <mpatrao@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: Invalid date        by                   #+#    #+#              #
#    Updated: 2023/06/20 13:53:43 by mpatrao          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


#    Updated: 2023/06/03 18:57:23 by gacorrei         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell
SRC			= main.c lexer.c signals.c utils.c utils_lexer.c utils_lists.c \
			parser.c commands.c export.c utils_export.c unset.c normal_command.c \
			directories.c executer.c utils_normal_command.c utils_directories.c \
			redirection.c pipes.c redirection_utils.c redirection_utils_2.c\
			logical_operators.c
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