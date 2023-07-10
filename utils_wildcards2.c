/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_wildcards2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 13:31:48 by gacorrei          #+#    #+#             */
/*   Updated: 2023/07/10 15:38:46 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Swaps nodes*/
void	swap(t_ll **temp)
{
	t_ll	*swap;

	swap = (*temp)->next;
	(*temp)->next = swap->next;
	swap->next = *temp;
	*temp = swap;
	return ;
}

/*Reorders list of matches alphabetically*/
void	reorder_list(t_ll **matches)
{
	t_ll	*temp;
	t_ll	*temp2;

	if (!*matches)
		return ;
	temp = *matches;
	temp2 = *matches;
	while (temp->next)
	{
		if (temp == *matches && temp->rank > temp->next->rank)
		{
			swap(&temp);
			*matches = temp;
			temp2 = temp;
			continue ;
		}
		else if (temp->rank > temp->next->rank)
		{
			swap(&temp);
			temp2->next = temp;
			temp = *matches;
			temp2 = *matches;
			continue ;
		}
		temp = temp->next;
		if (temp != (*matches)->next)
			temp2 = temp2->next;
	}
}
