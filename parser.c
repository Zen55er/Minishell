/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 09:39:46 by gacorrei          #+#    #+#             */
/*   Updated: 2023/05/26 11:38:53 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirection(t_data *data)
{
	(void) data;
	return ;
}

void	dollar(t_data *data)
{
	(void) data;
	return ;
}

int	command_call(t_data *data, int token, int command)
{
	if (command == ECHO)
		return (cmd_echo(data, token));
	if (command == CMD_CD)
		return (cmd_cd(data, token));
	if (command == CMD_PWD)
		return (cmd_pwd());
	if (command == CMD_EXPORT)
		return (cmd_export(data, token));
	if (command == CMD_UNSET)
		return (cmd_unset(data, token));
	if (command == CMD_ENV)
		return (cmd_env(data));
	if (command == CMD_EXIT)
		cmd_exit(data);
	normal_command(data, token);
	return (0);
}

int	command_check(char *input)
{
	if (!ft_strncmp(input, "echo", ft_strlen(input)))
		return (CMD_ECHO);
	if (!ft_strncmp(input, "cd", ft_strlen(input)))
		return (CMD_CD);
	if (!ft_strncmp(input, "pwd", ft_strlen(input)))
		return (CMD_PWD);
	if (!ft_strncmp(input, "export", ft_strlen(input)))
		return (CMD_EXPORT);
	if (!ft_strncmp(input, "unset", ft_strlen(input)))
		return (CMD_UNSET);
	if (!ft_strncmp(input, "env", ft_strlen(input)))
		return (CMD_ENV);
	if (!ft_strncmp(input, "exit", ft_strlen(input)))
		return (CMD_EXIT);
	return (0);
}

void	parser(t_data *data)
{
	int	i;
	int	command;

	i = -1;
	while (data->tokens[++i])
	{
		if (!ft_strncmp(data->tokens[i], "<", ft_strlen(data->tokens[i])))
			redirection(data);
		else if (!ft_strncmp(data->tokens[i], "$", ft_strlen(data->tokens[i])))
			dollar(data);
		command = command_check(data->tokens[i]);
		command_call(data, i, command);
	}
	return ;
}
