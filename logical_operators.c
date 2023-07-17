/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logical_operators.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 18:34:49 by gacorrei          #+#    #+#             */
/*   Updated: 2023/07/17 15:11:07 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*In executor, for parentheses cases, skips index to the final )*/
int	skip_parentheses(char **tokens, int i)
{
	int	flag;

	flag = 0;
	while (tokens[i])
	{
		if (!ft_strcmp(tokens[i], "("))
			flag++;
		if (!ft_strcmp(tokens[i], ")"))
			flag--;
		if (!flag)
			break ;
		i++;
	}
	return (i);
}

/*Determines if the next command should execute
based on logic operator and the previous command exit value*/
int	logical_choice(char **tokens, int token)
{
	if (!token)
		return (1);
	if ((!ft_strcmp(tokens[token], "&&") && !update_exit_code(0, 0))
		|| (!ft_strcmp(tokens[token], "||") && update_exit_code(0, 0)))
		return (2);
	return (0);
}

/*Test if str can be accessed as a command*/
int	check_single_cmd(t_data *data, char *cmd)
{
	int		i;
	char	*test;

	if (command_check(data, cmd, 1)
		|| (cmd[0] == '/' && check_path(data->path, cmd)))
		return (1);
	i = -1;
	while (data->path && data->path[++i])
	{
		test = ft_strjoin(data->path[i], cmd);
		if (!access(test, X_OK))
		{
			free(test);
			return (1);
		}
		else
			free(test);
	}
	return (0);
}
