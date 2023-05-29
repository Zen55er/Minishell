/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 09:39:46 by gacorrei          #+#    #+#             */
/*   Updated: 2023/05/29 10:09:25 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirection(t_data *data)
{
	(void) data;
	return ;
}

char	*find_var(t_ll *list, char *str)
{
	t_ll	*temp;
	int		len;

	temp = list;
	while (temp)
	{
		len = len_compare(str, temp->var);
		if (!ft_strncmp(str, temp->var, len))
			return (temp->value);
		temp = temp->next;
	}
	return (0);
}

void	dollar(t_data *data, int token)
{
	char	*str;

	token++;
	str = find_var(data->env, data->tokens[token]);
	if (!str)
		str = find_var(data->exp, data->tokens[token]);
	printf("%s\n", str);
	return ;
}

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
	// normal_command(data, token);
	return (0);
}

/*Checks if input matches specific functions*/
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
			dollar(data, i);
		else
		{
			command = command_check(data->tokens[i]);
			command_call(data, i, command);
		}
	}
	return ;
}
