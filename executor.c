/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatrao <mpatrao@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 09:08:32 by gacorrei          #+#    #+#             */
/*   Updated: 2023/07/13 12:10:57 by mpatrao          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Calls function to execute according to input*/
int	command_call(t_data *data, char **tokens, int tok, int cmd)
{
	if (cmd == CMD_ECHO)
		return (cmd_echo(tokens, tok));
	if (cmd == CMD_CD)
		return (cmd_cd(data, tokens, tok));
	if (cmd == CMD_PWD)
		return (cmd_pwd(data));
	if (cmd == CMD_EXPORT)
		return (cmd_export(data, tokens, tok));
	if (cmd == CMD_UNSET)
		return (cmd_unset(data, tokens, tok));
	if (cmd == CMD_ENV)
		return (cmd_env(data));
	if (cmd == CMD_EXIT)
		return (cmd_exit(data, tokens, tok));
	if (cmd == CMD_DIR)
		return (check_dir(tokens[tok]));
	return (normal_command(data, tokens, tok));
}

/*Checks if input matches specific functions*/
int	command_check(t_data *data, char *input, int flag)
{
	if (!ft_strcmp(input, "echo"))
		return (CMD_ECHO);
	if (!ft_strcmp(input, "cd"))
		return (CMD_CD);
	if (!ft_strcmp(input, "pwd"))
		return (CMD_PWD);
	if (!ft_strcmp(input, "export"))
		return (CMD_EXPORT);
	if (!ft_strcmp(input, "unset"))
		return (CMD_UNSET);
	if (!ft_strcmp(input, "env"))
		return (CMD_ENV);
	if (!ft_strcmp(input, "exit"))
		return (CMD_EXIT);
	if (!flag && !check_single_cmd(data, input)
		&& (!ft_strncmp(input, "./", 2) || input[0] == '/'))
		return (CMD_DIR);
	return (0);
}

/*If token was a directory skips to the next token.
If the token is the beginning of a subshell, skips to the closing parenthesis.
If the token is a delimiter and a logical operator, skips to the next token*/
int	skip_commands(char **tokens, int i, int command)
{
	if (command == CMD_DIR && !update_exit_code(0, 0))
		return (++i);
	while (tokens[++i])
	{
		if (!ft_strcmp(tokens[i], "("))
			i = skip_parentheses(tokens, i);
		if (delim_tok(tokens[i]))
		{
			if (ft_strcmp(tokens[i], "&&") && ft_strcmp(tokens[i], "||"))
				i++;
			break ;
		}
	}
	return (i);
}

/*Tests if next command should be skipped, if yes,updates index.*/
int	check_skip(t_data *data, char **tokens, int *i)
{
	if (!tokens[*i] || !tokens[*i][0])
		return (++(*i));
	if (check_pipe(tokens, data) != -1)
	{
		while (tokens[*i])
			++(*i);
		return (*i);
	}
	if ((!ft_strcmp(tokens[*i], "&&") || !ft_strcmp(tokens[*i], "||"))
		&& !logical_choice(tokens, *i))
	{
		*i = skip_commands(tokens, *i, 0);
		return (*i);
	}
	if (delim_tok(tokens[*i]))
	{
		if (!ft_strcmp(tokens[*i], "("))
			subshell(data, tokens, i);
		(*i)++;
		return (*i);
	}
	return (0);
}

/*Iterates through tokens and executes commands.
flag determines if function is called from main (0) or from subshell (1).*/
void	executor(t_data *data, char **tokens, int flag)
{
	int	i;
	int	command;

	i = 0;
	while (tokens[i])
	{
		if (check_skip(data, tokens, &i))
			continue ;
		quotes_delimiter_full(tokens, i);
		command = command_check(data, tokens[i], 0);
		set_exit_code(command_call(data, tokens, i, command));
		i = skip_commands(tokens, i, command);
	}
	if (flag)
	{
		set_exit_code(update_exit_code(0, 0));
		exit (update_exit_code(0, 0));
	}
	free_double(&(data->tokens));
}
