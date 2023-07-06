/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logical_operators.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 18:34:49 by gacorrei          #+#    #+#             */
/*   Updated: 2023/07/06 14:48:45 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

	if (command_check(cmd, 1)
		|| (cmd[0] == '/' && check_path(data->path, cmd)))
		return (1);
	i = -1;
	while (data->path[++i])
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
