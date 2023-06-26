/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 09:08:32 by gacorrei          #+#    #+#             */
/*   Updated: 2023/06/26 14:20:55 by gacorrei         ###   ########.fr       */
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
	return (normal_command(data, tokens, tok));
}

/*Checks if input matches specific functions*/
int	command_check(char *input)
{
	if (!ft_strncmp(input, "echo", ft_strlen("echo") + 1))
		return (CMD_ECHO);
	if (!ft_strncmp(input, "cd", ft_strlen("cd") + 1))
		return (CMD_CD);
	if (!ft_strncmp(input, "pwd", ft_strlen("pwd") + 1))
		return (CMD_PWD);
	if (!ft_strncmp(input, "export", ft_strlen("export") + 1))
		return (CMD_EXPORT);
	if (!ft_strncmp(input, "unset", ft_strlen("unset") + 1))
		return (CMD_UNSET);
	if (!ft_strncmp(input, "env", ft_strlen("env") + 1))
		return (CMD_ENV);
	if (!ft_strncmp(input, "exit", ft_strlen("exit") + 1))
		return (CMD_EXIT);
	return (0);
}

int	skip_commands(char **tokens, int i)
{
	while (tokens[++i])
	{
		if (!smart_compare(tokens[i], "("))
			while (tokens[i] && smart_compare(tokens[i], ")"))
				i++;
		if (delim(tokens[i]))
		{
			if (smart_compare(tokens[i], "&&")
				&& smart_compare(tokens[i], "||"))
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
		if (!smart_compare(tokens[i], "&&") || !smart_compare(tokens[i], "||"))
		{
			if (!logical_choice(tokens, i))
			{
				i = skip_commands(tokens, i);
				continue ;
			}
			i++;
		}
		if (delim(tokens[i]) && smart_compare(tokens[i], "&&")
			&& smart_compare(tokens[i], "||"))
		{
			if (!smart_compare(tokens[i], "("))
				subshell(data, tokens, &i);
			i++;
			continue ;
		}
		command = command_check(tokens[i]);
		set_exit_code(command_call(data, tokens, i, command));
		i = skip_commands(tokens, i);
	}
	if (flag)
	{
		set_exit_code(update_exit_code(0, 0));
		exit (update_exit_code(0, 0));
	}
	else
		return ;
}
