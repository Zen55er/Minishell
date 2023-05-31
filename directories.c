/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directories.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 11:36:43 by gacorrei          #+#    #+#             */
/*   Updated: 2023/05/31 13:52:06 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Updates current and previous directories*/
void	update_curr_prev(t_data *data)
{
	char	*temp;
	int		len;

	temp = 0;
	if (!data->curr_dir)
	{
		data->curr_dir = getcwd(data->curr_dir, 0);
		data->prev_dir = ft_strdup(data->curr_dir);
	}
	else
	{
		temp = getcwd(temp, 0);
		len = len_compare(temp, data->curr_dir);
		if (ft_strncmp(temp, data->curr_dir, len))
		{
			free(data->prev_dir);
			data->prev_dir = data->curr_dir;
			data->curr_dir = ft_strdup(temp);
		}
		free(temp);
	}
	return ;
}

/*Returns value of var from list, if it exists*/
char	*find_var(t_ll *list, char *str)
{
	int		len;

	while (list)
	{
		len = len_compare(list->var, str);
		if (!ft_strncmp(list->var, str, len))
			return (ft_strdup(list->value));
		list = list->next;
	}
	return (0);
}

/*Special cases for cd, ~ goes to $HOME, / goes 1 level above $HOME,
- goes to previous directory while writing that directory in terminal,
~- goes to previous directory whithout writing it,
otherwise, goes to path in input*/
char	*cd_cases(t_data *data, int token)
{
	char	*dir;

	if (!data->tokens[token] || !ft_strncmp(data->tokens[token], "~", 2))
		dir = find_var(data->env, "HOME");
	else if (!ft_strncmp(data->tokens[token], "-", 2))
	{
		dir = ft_strdup(data->prev_dir);
		printf("%s\n", dir);
	}
	else if (!ft_strncmp(data->tokens[token], "~-", 3))
		dir = ft_strdup(data->prev_dir);
	else
		dir = ft_strdup(data->tokens[token]);
	return (dir);
}

/*Changes directory and calls update_curr_prev*/
int	cmd_cd(t_data *data, int token)
{
	int		out;
	char	*dir;

	token++;
	if (data->tokens[token] && data->tokens[token + 1]
		&& !delim(data->tokens[token + 1]))
	{
		printf("cmd_cd: too many arguments\n");
		return (1);
	}
	dir = cd_cases(data, token);
	out = chdir(dir);
	free(dir);
	if (out)
	{
		perror("cmd_cd");
		return (1);
	}
	update_curr_prev(data);
	return (0);
}

/*Print current working directory*/
int	cmd_pwd(t_data *data)
{
	printf("%s\n", data->curr_dir);
	return (0);
}
