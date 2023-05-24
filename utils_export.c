/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 12:46:45 by gacorrei          #+#    #+#             */
/*   Updated: 2023/05/24 12:47:24 by gacorrei         ###   ########.fr       */
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

/*Prints linked list in alphabetical order*/
void	print_ordered(t_ll *list)
{
	int		i;
	int		j;
	t_ll	*temp;

	i = -1;
	j = list_size(list);
	while (++i < j)
	{
		temp = list;
		while (temp)
		{
			if (temp->rank == i)
			{
				printf("declare -x ");
				printf("%s", temp->var);
				if (temp->value)
					printf("=\"%s\"\n", temp->value);
				else
					printf("\n");
				break ;
			}
			temp = temp->next;
		}
	}
}
