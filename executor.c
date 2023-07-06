/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 09:08:32 by gacorrei          #+#    #+#             */
/*   Updated: 2023/07/06 14:50:34 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Checks if input is a directory.*/
int	check_dir(char *input)
{
	if (!input[0])
		return (OK_EXIT);
	if (!access(input, F_OK))
	{
		if (access(input, X_OK))
			print_error(input, 0, "Permission denied", 0);
		else
			print_error(input, 0, "Is a directory", 0);
		return (ERROR_EXECUTE_PERMISSIONS);
	}
	print_error(input, 0, "No such file or directory", 0);
	return (ERROR_WRONG_COMMAND);
}

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
int	command_check(char *input, int flag)
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
	if (!flag && (!ft_strncmp(input, "./", 2) || input[0] == '/'))
		return (CMD_DIR);
	return (0);
}

int	skip_commands(char **tokens, int i, int command)
{
	if (command == IS_DIR_FAIL)
		return (++i);
	while (tokens[++i])
	{
		if (!ft_strcmp(tokens[i], "("))
			while (tokens[i] && ft_strcmp(tokens[i], ")"))
				i++;
		if (delim(tokens[i]))
		{
			if (ft_strcmp(tokens[i], "&&")
				&& ft_strcmp(tokens[i], "||"))
				i++;
			break ;
		}
	}
	return (i);
}

/*Iterates through tokens and executes commands.
flag determines if function is called from main (0) or from subshell (1).*/
void	executor(t_data *data, char **tokens, int flag)
{
	int	i;
	int	command;

	i = 0;
	// redirection(data);
	while (tokens[i])
	{
		if ((!tokens[i] || !tokens[i][0]) && ++i)
			continue ;
		if (!ft_strcmp(tokens[i], "&&") || !ft_strcmp(tokens[i], "||"))
		{
			if (!logical_choice(tokens, i))
			{
				i = skip_commands(tokens, i, 0);
				continue ;
			}
			i++;
		}
		if (delim(tokens[i]) && ft_strcmp(tokens[i], "&&")
			&& ft_strcmp(tokens[i], "||"))
		{
			if (!ft_strcmp(tokens[i], "("))
				subshell(data, tokens, &i);
			i++;
			continue ;
		}
		command = command_check(tokens[i], 0);
		set_exit_code(command_call(data, tokens, i, command));
		i = skip_commands(tokens, i, command);
	}
	if (flag)
	{
		set_exit_code(update_exit_code(0, 0));
		exit (update_exit_code(0, 0));
	}
	else
		return ;
}
