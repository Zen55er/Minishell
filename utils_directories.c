/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_directories.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 11:16:32 by gacorrei          #+#    #+#             */
/*   Updated: 2023/06/06 12:48:55 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_dir(t_data *data, char *dir)
{
	t_ll	*temp;
	int		len;

	temp = data->env;
	while (temp)
	{
		len = len_compare(temp->var, dir);
		if (!ft_strncmp(temp->var, dir, len))
			return (temp->value);
		temp = temp->next;
	}
	return (0);
}

void	update_env_dir(t_data *data, char *dir, char *new_dir)
{
	t_ll	*temp;
	int		len;

	temp = data->env;
	while (temp)
	{
		len = len_compare(temp->var, dir);
		if (!ft_strncmp(temp->var, dir, len))
		{
			free(temp->value);
			temp->value = ft_strdup(new_dir);
			break ;
		}
		temp = temp->next;
	}
	return ;
}
