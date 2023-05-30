/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 09:39:46 by gacorrei          #+#    #+#             */
/*   Updated: 2023/05/30 13:39:34 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirection(t_data *data)
{
	(void) data;
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
	normal_command(data, token);
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

/*Returns variable value, if it exists*/
char	*expansion(t_data *data, char	*str)
{
	int		i;
	char	*test;
	char	*val;

	i = 0;
	while (str[++i] && str[i] != '$')
		continue ;
	if (i <= 1)
		return (0); /*CHECK IF THIS IS OK*/
	test = ft_substr(str, 1, i - 1);
	if (!test)
		return (0); /*CHECK IF THIS IS OK*/
	val = find_var(data->env, test);
	if (!val)
		val = find_var(data->exp, test);
	return (0);
}

/*Returns new string with text formatted according to quote type*/
char	*quotes(char *str)
{
	(void) str;
	return (0);
}

/*Parses cases with $ and quotes*/
void	parser(t_data	*data)
{
	int	i;

	return ;
	i = -1;
	while (data->tokens[++i])
	{
		if (data->tokens[i][0] == '$')
			data->tokens[i] = expansion(data, data->tokens[i]);
		else if (data->tokens[i][0] == '\'' || data->tokens[i][0] == '\"')
			data->tokens[i] = quotes(data, data->tokens[i]);
	}
}

void	executer(t_data *data)
{
	int	i;
	int	command;

	i = 0;
	while (data->tokens[i])
	{
		if (!ft_strncmp(data->tokens[i], "<", ft_strlen(data->tokens[i])))
			redirection(data);
		else
		{
			command = command_check(data->tokens[i]);
			command_call(data, i, command);
		}
		while (data->tokens[++i])
		{
			if (delim(data->tokens[i]))
				break ;
		}
	}
	return ;
}
