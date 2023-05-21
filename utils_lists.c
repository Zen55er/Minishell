/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lists.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 08:46:39 by gacorrei          #+#    #+#             */
/*   Updated: 2023/05/21 09:09:30 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Creates a new node*/
t_ll	*new_node(char *content)
{
	t_ll	*node;

	node = malloc(sizeof(t_ll));
	if (!node)
		return (0);
	node->content = content;
	node->next = 0;
	return (node);
}

/*Returns the address of the final node in list*/
t_ll	*list_last(t_ll *list)
{
	if (!list)
		return (0);
	while (list->next)
		list = list->next;
	return (list);
}

/*Adds node to the start of the list*/
void	node_add_front(t_ll **list, t_ll *node)
{
/*IS THIS EVEN USEFUL?*/
	if (!node)
		return ;
	if (!list)
	{
		*list = node;
		return ;
	}
	node->next = *list;
	*list = node;
	return ;
}

/*Adds node to the end of the list*/
void	node_add_back(t_ll **list, t_ll *node)
{
	t_ll	*temp;

	if (!node)
		return ;
	if (!*list)
	{
		*list = node;
		return ;
	}
	temp = list_last(*list);
	temp->next = node;
	return ;
}
