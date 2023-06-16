/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 14:13:43 by gacorrei          #+#    #+#             */
/*   Updated: 2023/06/16 11:46:50 by gacorrei         ###   ########.fr       */
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

# define CMD_ECHO 3
# define CMD_CD 4
# define CMD_PWD 5
# define CMD_EXPORT 6
# define CMD_UNSET 7
# define CMD_ENV 8
# define CMD_EXIT 9

# define OK_EXIT 0
# define ERROR_EXIT 1
# define ERROR_SYNTAX 2
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
char	**lexer(t_data *data, char **input);

/*utils_lexer.c*/
int		char_finder(char *str, char c);
int		forbidden(char *str);
int		delim(char *str, int flag);
int		quote_case(char *str);
int		special_dollar(char *str, int flag);

/*utils_lexer2.c*/
int		bad_substitution(char *str, int end);
int		syntax_error(char *str);
int		unexpected_eof(char c);
int		missing_input(char **input, char match);
char	get_match(char c);
int		validate_input(char **input);

/*logical_operators.c*/
int		logical_choice(t_data *data, int token);
int		check_single_cmd(t_data *data, char *cmd);
int		is_cmd(t_data *data, char *str);
int		logical_search(t_data *data, char *str);
int		check_and_or(t_data *data, char *str);

/*parser.c*/
char	*update_expansion(t_data *data, char *val, char *test);
char	*expansion(t_data *data, char	*str);
char	*quotes(t_data *data, char *str);
char	*quote_str(t_data *data, char *str);
int		parser(t_data *data);

/*utils_parser.c*/
char	*get_exit_code(t_data *data, char *str1, char *str2);
char	*get_section(t_data *data, char *str, int i, int j);
void	fix_tokens_wc(t_data *data, int *i);
int		check_consecutive(char *tok1, char *tok2);
int		validate_tokens(char **tokens);

/*executor.c*/
int		command_call(t_data *data, int token, int command);
int		command_check(char *input);
void	executor(t_data *data);

/*pipes*/
int		pipeline(t_data *data, int i);
void	pipes(t_data *data, int i);

/*redirection*/
int		redirection(t_data *data);

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

/*wildcards.c*/
void	add_list_tokens(char **new_tok, t_ll *matches, int i);
int		old_tokens(t_data *data);
int		add_tokens(t_data *data, t_ll *matches, int token);
int		compare_wc(char *token, char *content);
t_ll	*expand_wildcards(char *token);

/*utils_wildcards.c*/
void	double_increment(int *i, int *j);
void	found_wildcard(int *i, int *j, int *prev_wc, int *backtrack);
void	return_to_previous(int *i, int *j, int *prev_wc, int *backtrack);
int		final_wc_check(int i, char *token);

#endif
