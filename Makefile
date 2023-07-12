# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpatrao <mpatrao@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: Invalid date        by                   #+#    #+#              #
#    Updated: 2023/07/12 14:05:10 by mpatrao          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell
SRC			= main.c lexer.c signals.c utils.c utils_lexer.c utils_lists.c \
			parser.c commands.c export.c utils_export.c unset.c normal_command.c \
			directories.c utils_normal_command.c utils_directories.c \
			redirection.c pipes.c pipes_utils.c redirection_utils.c \
			logical_operators.c executor.c wildcards.c utils_wildcards.c \
			utils_parser.c utils_lexer2.c utils_lexer3.c utils_free.c exit_code.c \
			subshell.c utils_parser2.c utils_wildcards2.c

CC			= @cc
LIBFT		= libft/libft.a
LIBFT_DIR	= libft
CFLAGS		= -Wall -Wextra -Werror -g3 -lreadline

all:		$(NAME)

$(NAME):	$(SRC)
			@$(MAKE) --no-print-directory -C $(LIBFT_DIR)
			$(CC) $(CFLAGS) $(^) -o $(@) $(LIBFT) -fsanitize=address,undefined

clean:
			@$(MAKE) --no-print-directory -C $(LIBFT_DIR) clean

fclean:		clean
			@$(MAKE) --no-print-directory -C $(LIBFT_DIR) fclean
			@rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re