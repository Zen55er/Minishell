/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_normal_command.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 09:16:08 by gacorrei          #+#    #+#             */
/*   Updated: 2023/06/01 09:20:43 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Finds matching quote for awk cases*/
int	awk_quotes(char *cmd, char c, int *i)
{
	int	len;

	*i += 1;
	len = ft_strlen(cmd + 1);
	if (cmd[len] == c)
		return (len - 1);
	return (0);
}

/*Special case for awk calls.*/
int	awk_cmd(t_cmds **cmds, char *cmd)
{
	int	i;
	int	j;

	i = 3;
	j = 0;
	while (cmd[i] == ' ')
		i++;
	if (cmd[i] == 34 || cmd[i] == 39)
		j = awk_quotes(&cmd[i], cmd[i], &i);
	if (j == 0)
		return (1);
	(*cmds)->cmd_args = (char **)malloc(sizeof(char *) * 3);
	(*cmds)->cmd_args[0] = ft_substr(cmd, 0, 3);
	if (j)
		(*cmds)->cmd_args[1] = ft_substr(&cmd[i], 0, j);
	else
		(*cmds)->cmd_args[1] = ft_strdup(&cmd[i]);
	(*cmds)->cmd_args[2] = 0;
	return (0);
}

/*Tests commands against path*/
void	test_cmd(char **paths, t_cmds **cmds)
{
	int		i;
	char	*test;

	i = -1;
	while (paths[++i])
	{
		test = ft_strjoin(paths[i], (*cmds)->cmd_args[0]);
		if (!access(test, F_OK & X_OK) && !(*cmds)->cmd)
			(*cmds)->cmd = test;
		else
			free(test);
		if ((*cmds)->cmd)
			break ;
	}
	return ;
}

char	*get_full_var(char *var, char *value)
{
	char	*temp1;
	char	*temp2;

	temp1 = ft_strjoin(var, "=");
	temp2 = ft_strjoin(temp1, value);
	free(temp1);
	return (temp2);
}

/*Checks if the given command is in PATH*/
int	check_path(char **paths, char *cmd)
{
	int	i;

	i = -1;
	while (paths[++i])
	{
		if (ft_strncmp(paths[i], cmd, ft_strlen(paths[i])) == 0)
			return (1);
	}
	return (0);
}
