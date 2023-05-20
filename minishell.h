/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 14:13:43 by gacorrei          #+#    #+#             */
/*   Updated: 2023/05/19 14:25:27 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <dirent.h>
# include <string.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <curses.h>
# include <term.h>

/*main.c*/

/*lexer.c*/
int		char_finder(char *str, char c);
void	get_find(char *str, char *find);
int		quote_case(char *str, int i);
int		forbidden(char *str);
int		count_tokens(char *str);
void	set_tokens(char **tokens, char *str);
char	**lexer(char *input);

/*signals.c*/
void	signal_handler(int sig);
void	signal_global(void);

/*utils*/
void	free_tokens(char **tokens);
void	free_all(char *input, char **tokens);
#endif
