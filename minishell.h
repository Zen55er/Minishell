/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatrao <mpatrao@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 14:13:43 by gacorrei          #+#    #+#             */
/*   Updated: 2023/06/14 14:33:42 by mpatrao          ###   ########.fr       */
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

# define CMD_ECHO 2
# define CMD_CD 3
# define CMD_PWD 4
# define CMD_EXPORT 5
# define CMD_UNSET 6
# define CMD_ENV 7
# define CMD_EXIT 8

# define OK_EXIT 0
# define ERROR_EXIT 1
# define ERROR_WRONG_COMMAND 127

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

typedef struct cmd_st
{
	char			**cmd;
	int				num_redir;
	int				num_pipes;
	int				redir_in;
	int				redir_out;
	struct t_cmd_st	*next;
	struct t_cmd_st	*prev;
}	t_cmd_st;

typedef struct s_data
{
	char		**tokens;
	t_ll		*env;
	t_ll		*exp;
	char		**path;
	char		*curr_dir;
	char		*prev_dir;
	int			fdin;
	int			fdout;
	int			lastfdout;
	t_cmd_st	*cmd_st;
	int			last_exit;
	int			logic_operator;
}			t_data;

/*main.c*/
void	update_path(t_data *data);
void	prep_env(t_data *data, char **envp);
char	*build_prompt(t_data *data);

/*lexer.c*/
int		other(char *str, int flag);
int		tok_len(char *str, int i, int flag);
int		count_tokens(t_data *data, char *str);
void	set_tokens(t_data *data, char **tokens, char *str);
char	**lexer(t_data *data, char *input);

/*utils_lexer.c*/
int		char_finder(char *str, char c);
void	get_find(char *str, char *find);
int		forbidden(char *str);
int		delim(char *str, int flag);
int		quote_case(char *str);

/*logical_operators.c*/
int		logical_choice(t_data *data, int token);
int		check_single_cmd(t_data *data, char *cmd);
int		is_cmd(t_data *data, char *str);
int		logical_search(t_data *data, char *str);
int		check_and_or(t_data *data, char *str);

/*parser.c*/
char	*update_expansion(t_data *data, char *val, char **test);
char	*expansion(t_data *data, char	*str);
char	*quotes(t_data *data, char *str);
void	parser(t_data *data);

/*executer.c*/
int		command_call(t_data *data, int token, int command);
int		command_check(char *input);
void	executer(t_data *data);

/*pipes*/
int		pipeline(t_data *data, int i);
void	pipes(t_data *data, int i);

/*redirection*/
int		redirection(t_data *data);

/*redirections utils*/
void	count_pipes(t_data *data);
int		count_args(t_data *data, int j);

/*commands.c*/
int		cmd_echo(t_data *data, int tok);
int		cmd_env(t_data *data);
void	cmd_exit(t_data *data);

/*normal_command.c*/
char	**prep_cmds(t_data *data, int token, char *cmd);
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
char	*search_dir(char *pre, char *post);
char	*test_wildcard(char *token, int wildcard);
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
char	*get_end_cmd(char *str);
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
