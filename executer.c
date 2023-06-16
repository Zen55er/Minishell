/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatrao <mpatrao@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 09:08:32 by gacorrei          #+#    #+#             */
/*   Updated: 2023/06/16 14:52:43 by mpatrao          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Calls function to execute according to input*/
int	command_call(t_data *data, int token, int command)
{
	if (command == CMD_ECHO)
		return (cmd_echo(data, token));
	if (command == CMD_CD)
		return (cmd_cd(data, token));
	if (command == CMD_PWD)
		return (cmd_pwd(data));
	if (command == CMD_EXPORT)
		return (cmd_export(data, token));
	if (command == CMD_UNSET)
		return (cmd_unset(data, token));
	if (command == CMD_ENV)
		return (cmd_env(data));
	if (command == CMD_EXIT)
		cmd_exit(data);
	return (normal_command(data, token));
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
void	executer(t_data *data)
{
	int	i;
	int	command;

	i = 0;
	if (redirection(data))
		destroy_cmd_st();
	while (data->tokens[i])
	{
		if (delim(data->tokens[i], 1))
		{
			i++;
			continue ;
		}
		else if (logical_choice(data, i))
		{
			command = command_check(data->tokens[i]);
			data->last_exit = command_call(data, i, command);
		}
		while (data->tokens[++i])
		{
			if (delim(data->tokens[i], 1) && ++i)
				break ;
		}
	}
	return ;
}
