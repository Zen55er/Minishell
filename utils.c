/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 12:48:32 by gacorrei          #+#    #+#             */
/*   Updated: 2023/05/25 12:05:19 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Returns length of largest string*/
int	len_compare(char *str1, char *str2)
{
	int	len1;
	int	len2;

	len1 = ft_strlen(str1);
	len2 = ft_strlen(str2);
	if (len1 >= len2)
		return (len1);
	else
		return (len2);
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
