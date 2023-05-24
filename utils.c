/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 12:48:32 by gacorrei          #+#    #+#             */
/*   Updated: 2023/05/24 11:18:26 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Sets ranks to 0*/
void	rank_reset(t_ll *list)
{
	t_ll	*temp;

	temp = list;
	while (temp)
	{
		temp->rank = 0;
		temp = temp->next;
	}
}

/*Sets ranks for each entry in list for export function*/
void	list_ranking(t_ll *list)
{
	int		len;
	t_ll	*temp;
	t_ll	*temp2;

	rank_reset(list);
	temp = list;
	while (temp)
	{
		temp2 = list;
		while (temp2)
		{
			if (ft_strlen(temp->var) >= ft_strlen(temp2->var))
				len = ft_strlen(temp->var);
			else
				len = ft_strlen(temp2->var);
			if (ft_strncmp(temp->var, temp2->var, len) > 0)
				temp->rank++;
			temp2 = temp2->next;
		}
		temp = temp->next;
	}
}

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
