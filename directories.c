/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directories.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 11:36:43 by gacorrei          #+#    #+#             */
/*   Updated: 2023/07/06 08:38:46 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Updates current and previous directories*/
void	update_curr_prev(t_data *data)
{
	char	*temp;

	if (data->curr_dir)
	{
		temp = 0;
		temp = getcwd(temp, 0);
		if (ft_strcmp(temp, data->curr_dir))
		{
			update_env_dir(data, "OLDPWD", data->curr_dir);
			update_env_dir(data, "PWD", temp);
		}
		free(temp);
	}
	data->curr_dir = get_dir(data, "PWD");
	data->prev_dir = get_dir(data, "OLDPWD");
	return ;
}

/*Returns value of var from list, if it exists*/
char	*find_var(t_ll *list, char *str)
{
	while (list)
	{
		if (!ft_strcmp(list->var, str))
			return (ft_strdup(list->value));
		list = list->next;
	}
	return (0);
}

/*Special cases for cd, ~ goes to $HOME, / goes 1 level above $HOME,
- goes to previous directory while writing that directory in terminal,
~- goes to previous directory whithout writing it,
otherwise, goes to path in input*/
char	*cd_cases(t_data *data, char **tokens, int token)
{
	char	*dir;

	if (!tokens[token] || delim(tokens[token])
		|| !ft_strcmp(tokens[token], "~"))
		dir = find_var(data->env, "HOME");
	else if (!ft_strcmp(tokens[token], "-"))
	{
		dir = ft_strdup(data->prev_dir);
		printf("%s\n", dir);
	}
	else if (!ft_strcmp(tokens[token], "~-"))
		dir = ft_strdup(data->prev_dir);
	else
		dir = ft_strdup(tokens[token]);
	return (dir);
}

/*Changes directory and calls update_curr_prev*/
int	cmd_cd(t_data *data, char **tokens, int token)
{
	int		out;
	char	*dir;

	token++;
	if (!tokens[token][1] || (tokens[token]
		&& tokens[token + 1]
		&& !delim(tokens[token])
		&& !delim(tokens[token + 1])))
	{
		printf("minishell: cd: too many arguments\n");
		return (ERROR_EXIT);
	}
	dir = cd_cases(data, tokens, token);
	out = chdir(dir);
	free(dir);
	if (out)
	{
		perror("cmd_cd");
		return (ERROR_EXIT);
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
