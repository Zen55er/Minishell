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

/*Creates a new node, if flag is 1 fills var and value,
otherwise only fills var (for exporting variables without proper formatting)*/
t_ll	*new_node(char *content, int flag)
{
	t_ll	*node;
	int		i;

	i = 0;
	node = malloc(sizeof(t_ll));
	if (!node)
		return (0);
	if (flag)
	{
		while (content[i] && content[i] != '=')
			i++;
		node->var = ft_substr(content, 0, i);
		node->value = ft_substr(content, i + 1, ft_strlen(content) - i);
	}
	else
	{
		node->var = ft_strdup(content);
		node->value = 0;
	}
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

int	list_size(t_ll *list)
{
	int	n;

	if (!list)
		return (0);
	n = 0;
	while (list)
	{
		list = list->next;
		n++;
	}
	return (n);
}

/*Adds node to the start of the list*/
void	node_add_front(t_ll **list, t_ll *node)
{
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
