/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 12:48:32 by gacorrei          #+#    #+#             */
/*   Updated: 2023/05/22 16:01:26 by gacorrei         ###   ########.fr       */
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

/*Frees everything*/
void	free_all(char *input, char *input2, t_data *data)
{
	if (input)
		free(input);
	if (input2)
		free(input2);
	if (data && data->path)
		free_double(data->path);
	if (data && data->env)
		free_list(&data->env);
	if (data && data->tokens)
		free_double(data->tokens);
	return ;
}
