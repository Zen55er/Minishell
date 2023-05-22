/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lists.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 08:46:39 by gacorrei          #+#    #+#             */
/*   Updated: 2023/05/22 15:57:48 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Creates a new node*/
t_ll	*new_node(char *content)
{
	t_ll	*node;
	int		i;

	i = 0;
	while (content[i] && content[i] != '=')
		i++;
	node = malloc(sizeof(t_ll));
	if (!node)
		return (0);
	node->var = ft_substr(content, 0, i);
	node->value = ft_substr(content, i + 1, ft_strlen(content) - i);
	node->rank = 0;
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
