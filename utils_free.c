/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 12:08:51 by gacorrei          #+#    #+#             */
/*   Updated: 2023/06/22 10:31:54 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Frees char***/
void	free_double(char **array)
{
	int	i;

	i = -1;
	while (array[++i])
	{
		if (array[i])
			free(array[i]);
	}
	free(array);
}

/*Fress linked list*/
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
		free_double(cmds->cmd_args);
		free(cmds->cmd);
		free(cmds);
	}
	if (env2d)
		free_double(env2d);
}

/*Frees everything*/
void	free_all(char *input, t_data *data)
{
	if (input)
		free(input);
	if (data && data->path)
		free_double(data->path);
	if (data && data->tokens)
		free_double(data->tokens);
	if (data && data->env)
		free_list(&data->env);
	if (data && data->exp)
		free_list(&data->exp);
	return ;
}
