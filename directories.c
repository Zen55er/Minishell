/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directories.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 11:36:43 by gacorrei          #+#    #+#             */
/*   Updated: 2023/06/02 12:07:38 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Updates current and previous directories*/
void	update_curr_prev(t_data *data)
{
	char	*temp;
	int		len;

	if (data->curr_dir)
	{
		temp = 0;
		temp = getcwd(temp, 0);
		len = len_compare(temp, data->curr_dir);
		if (ft_strncmp(temp, data->curr_dir, len))
		{
			update_env_dir(data, "OLDPWD", data->curr_dir);
			update_env_dir(data, "PWD", temp);
			free(temp);
		}
	}
	data->curr_dir = get_dir(data, "PWD");
	data->prev_dir = get_dir(data, "OLDPWD");
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
		return (CD_TOO_MANY_ARGS);
	}
	dir = cd_cases(data, token);
	out = chdir(dir);
	free(dir);
	if (out)
	{
		perror("cmd_cd");
		return (CD_ERROR_DIR_CHANGE);
	}
	update_curr_prev(data);
	return (OK_EXIT);
}

/*Print current working directory*/
int	cmd_pwd(t_data *data)
{
	printf("%s\n", data->curr_dir);
	return (OK_EXIT);
}
