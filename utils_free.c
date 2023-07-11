/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 12:08:51 by gacorrei          #+#    #+#             */
/*   Updated: 2023/07/11 11:22:00 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Runs free and returns ret.
Used to save space in other functions.*/
int	int_free(void *str, int ret)
{
	free(str);
	return (ret);
}

/*Frees char***/
void	free_double(char ***array)
{
	int	i;

	if (!(*array))
		return ;
	i = -1;
	while ((*array)[++i])
	{
		if ((*array)[i])
			free((*array)[i]);
	}
	free(*array);
	*array = 0;
	return ;
}

/*Frees linked list*/
void	free_list(t_ll **list)
{
	t_ll	*temp;

	while (*list)
	{
		temp = (*list)->next;
		free((*list)->var);
		free((*list)->value);
		free(*list);
		*list = temp;
	}
}

/*When there is an error in a child process,
frees command struct and env2d*/
void	free_child(t_cmds *cmds, char **env2d)
{
	if (cmds)
	{
		free_double(&(cmds->cmd_args));
		free(cmds->cmd);
		free(cmds);
	}
	if (env2d)
		free_double(&env2d);
}

/*Frees everything*/
void	free_all(char *input, t_data *data)
{
	rl_clear_history();
	if (input)
		free(input);
	if (data && data->path)
		free_double(&(data->path));
	if (data && data->tokens)
		free_double(&(data->tokens));
	if (data && data->env)
		free_list(&data->env);
	return ;
}
