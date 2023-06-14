/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logical_operators.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 18:34:49 by gacorrei          #+#    #+#             */
/*   Updated: 2023/06/14 10:12:47 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Determines if the current command should execute
based on preceding logic operator and the previous command exit value*/
int	logical_choice(t_data *data, int token)
{
	if (!token || (ft_strncmp(data->tokens[token - 1], "&&", 3)
			|| (ft_strncmp(data->tokens[token - 1], "||", 3))))
		return (1);
	if ((!ft_strncmp(data->tokens[token - 1], "&&", 3) && !data->last_exit)
		|| (!ft_strncmp(data->tokens[token - 1], "||", 3) && data->last_exit))
		return (1);
	return (0);
}

/*Test if str can be accessed as a command*/
int	check_single_cmd(t_data *data, char *cmd)
{
	int		i;
	char	*test;

	i = -1;
	while (data->path[++i])
	{
		test = ft_strjoin(data->path[i], cmd);
		if (!access(test, F_OK & X_OK))
		{
			free(test);
			return (1);
		}
		else
			free(test);
	}
	return (0);
}

/*Checks if first word is a valid command*/
int	is_cmd(t_data *data, char *str)
{
	int		i;
	char	*test;

	i = 0;
	while (!ft_isspace(str[i]) && str[i] != ')')
		i++;
	test = ft_substr(str, 0, i);
	if (command_check(test)
		|| (test[0] == '/' && check_path(data->path, test))
		|| (!ft_strncmp(test, "awk ", 4) || !ft_strncmp(test, "sed ", 4))
		|| check_single_cmd(data, test))
	{
		free (test);
		return (1);
	}
	free (test);
	return (0);
}

/*When a '(' is found, if it contains a delimiter,
only '(' is considered for the current token
and the logical operator flag is set.*/
int	logical_search(t_data *data, char *str)
{
	int	i;
	int	flag;

	i = 0;
	while (ft_isspace(str[++i]))
		continue ;
	flag = 0;
	while (str[i])
	{
		if (is_cmd(data, &str[i]))
			return (++data->logic_operator);
		if (delim(&str[i], 0))
			flag = 1;
		else if (str[i] == ')')
		{
			flag++;
			break ;
		}
		i++;
	}
	if (flag == 2)
		return (++data->logic_operator);
	return (0);
}

/*Special cases for possible logic operators. If a ')' is found,
it is only considered for the current token if the logic operator
flag is active in data. Also calls logical search, which will can the flag*/
int	check_and_or(t_data *data, char *str)
{
	if (str[0] == ')' && data->logic_operator)
	{
		data->logic_operator = 0;
		return (1);
	}
	else if (str[0] == ')' && !data->logic_operator)
		return (0);
	if (str[0] == '(')
		return (logical_search(data, str));
	return (0);
}
