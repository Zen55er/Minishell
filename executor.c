/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatrao <mpatrao@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 09:08:32 by gacorrei          #+#    #+#             */
/*   Updated: 2023/06/23 13:46:09 by gacorrei         ###   ########.fr       */
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

/*Iterates through tokens and executes commands*/
void	executor(t_data *data, char **tokens)
{
	int	i;
	int	command;

	i = 0;
	// redirection(data);
	while (tokens[i])
	{
		if (delim(tokens[i]))
		{
			if (!smart_compare(tokens[i], "("))
				subshell(data, &i);
			i++;
			continue ;
		}
		else if (logical_choice(data, i))
		{
			command = command_check(tokens[i]);
			set_exit_code(command_call(data, tokens, i, command));
		}
		while (tokens[++i])
		{
			if (delim(tokens[i]) && ++i)
				break ;
		}
	}
	return ;
}
