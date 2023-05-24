/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 14:13:43 by gacorrei          #+#    #+#             */
/*   Updated: 2023/05/24 11:56:49 by gacorrei         ###   ########.fr       */
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

typedef struct s_ll
{
	char			*var;
	char			*value;
	int				rank;
	struct s_ll		*next;
}					t_ll;

typedef struct s_data
{
	char	**tokens;
	t_ll	*env;
	t_ll	*exp;
	char	**path;
}			t_data;

/*main.c*/
void	prep_env_path(t_data *data, char **envp);

/*lexer.c*/
int		other(char *str, int flag);
int		tok_len(char *str, int i, int flag);
int		count_tokens(char *str);
void	set_tokens(char **tokens, char *str);
char	**lexer(char *input);

/*utils_lexer.c*/
int		char_finder(char *str, char c);
void	get_find(char *str, char *find);
int		forbidden(char *str);
int		delim(char *str);
int		quote_case(char *str);

/*parser.c*/
int		command_check(t_data *data, char *input, int token);
void	parser(t_data *data);

/*commands.c*/
int		cmd_echo(t_data *data);
int		cmd_cd(t_data *data);
int		cmd_pwd(t_data *data);
int		cmd_unset(t_data *data);
int		cmd_env(t_data *data);
void	cmd_exit(t_data *data);

/*export.c*/
int		check_entry(t_data *data, t_ll *list, int tok, int i);
void	add_to_exp(t_data *data, int tok, int i);
int		export_arg(t_data *data, int token);
void	print_ordered(t_ll *list);
int		cmd_export(t_data *data, int token);

/*signals.c*/
void	signal_handler(int sig);
void	signal_global(void);

/*utils*/
void	rank_reset(t_ll *env);
void	list_ranking(t_ll *env);
void	free_double(char **tokens);
void	free_all(char *input, t_data *data);

/*utils_lists.c*/
t_ll	*new_node(char *content, int flag);
t_ll	*list_last(t_ll *list);
int		list_size(t_ll *list);
void	node_add_front(t_ll **list, t_ll *node);
void	node_add_back(t_ll **list, t_ll *node);

#endif
