/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 14:13:43 by gacorrei          #+#    #+#             */
/*   Updated: 2023/05/31 14:06:12 by gacorrei         ###   ########.fr       */
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
# include <sys/wait.h>
# include <dirent.h>
# include <string.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <errno.h>

# define CMD_ECHO 1
# define CMD_CD 2
# define CMD_PWD 3
# define CMD_EXPORT 4
# define CMD_UNSET 5
# define CMD_ENV 6
# define CMD_EXIT 7

typedef struct s_cmds
{
	char	*cmd;
	char	**cmd_args;
}			t_cmds;

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
	char	*curr_dir;
	char	*prev_dir;
}			t_data;

/*main.c*/
void	update_path(t_data  *data);
void	prep_env(t_data *data, char **envp);
char	*build_prompt(t_data *data);

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
char	*update_expansion(t_data *data, char *val, char **test);
char	*expansion(t_data *data, char	*str);
char	*quotes(t_data *data, char *str);
void	parser(t_data *data);

/*executer.c*/
void	redirection(t_data *data);
int		command_call(t_data *data, int token, int command);
int		command_check(char *input);
void	executer(t_data *data);

/*commands.c*/
int		cmd_echo(t_data *data, int tok);
int		cmd_env(t_data *data);
void	cmd_exit(t_data *data);

/*normal_command.c*/
char	**prep_cmds(t_data *data, int token);
t_cmds	*get_cmd(t_data *data, int token);
char	**get_env2d(t_ll *env);
void	child(t_data *data, int token);
int		normal_command(t_data *data, int token);

/*utils_normal_command.c*/
int		awk_quotes(char *cmd, char c, int *i);
int		awk_cmd(t_cmds **cmds, char *cmd);
void	test_cmd(char **paths, t_cmds **cmds);
char	*get_full_var(char *var, char *value);
int		check_path(char **paths, char *cmd);

/*directories*/
void	update_curr_prev(t_data *data);
char	*find_var(t_ll *list, char *str);
char	*cd_cases(t_data *data, int token);
int		cmd_cd(t_data *data, int token);
int		cmd_pwd(t_data *data);

/*utils_directories.c*/
char	*get_dir(t_data *data, char *dir);
void	update_env_dir(t_data *data, char *dir, char *new_dir);

/*export.c*/
int		check_entry(t_data *data, t_ll *list, int tok, int i);
void	add_to_exp(t_data *data, int tok, int i);
int		export_arg(t_data *data, int tok);
int		cmd_export(t_data *data, int token);

/*unset.c*/
int		unset_var(t_ll **list, int count);
int		check_unset(t_data *data, t_ll **list, int token);
int		cmd_unset(t_data *data, int tok);

/*utils_export.c*/
void	rank_reset(t_ll *env);
void	list_ranking(t_ll *env);
void	print_ordered(t_ll *list);

/*signals.c*/
void	signal_handler(int sig);
void	signal_global(void);

/*utils*/
int		len_compare(char *str1, char *str2);
void	free_double(char **tokens);
void	free_list(t_ll **list);
void	free_all(char *input, t_data *data);

/*utils_lists.c*/
t_ll	*new_node(char *content, int flag);
t_ll	*list_last(t_ll *list);
int		list_size(t_ll *list);
void	node_add_front(t_ll **list, t_ll *node);
void	node_add_back(t_ll **list, t_ll *node);

#endif
