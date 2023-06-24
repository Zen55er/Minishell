/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 09:27:09 by gacorrei          #+#    #+#             */
/*   Updated: 2023/06/23 13:44:55 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Frees selected node's memory and connects previous node to next*/
int	unset_var(t_ll **list, int count)
{
	t_ll	*temp;
	t_ll	*temp2;

	if (list_size(*list) == 1)
	{
		free((*list)->var);
		free((*list)->value);
		free(*list);
		*list = 0;
		return (1);
	}
	temp = *list;
	temp2 = *list;
	while (--count > 0)
	{
		temp = temp->next;
		temp2 = temp2->next;
	}
	temp2 = temp2->next;
	temp->next = temp->next->next;
	temp2->next = 0;
	free(temp2->var);
	free(temp2->value);
	free(temp2);
	return (1);
}

/*Checks each node of list until it finds one which has a matching variable
before calling unset_var*/
int	check_unset(t_data *data, t_ll **list, int token)
{
	t_ll	*temp;
	int		len;
	int		count;

	if (!(*list))
		return (0);
	temp = *list;
	count = 0;
	while (temp)
	{
		len = len_compare(data->tokens[token], temp->var);
		if (!ft_strncmp(data->tokens[token], temp->var, len))
			return (unset_var(list, count));
		temp = temp->next;
		count++;
	}
	return (0);
}

/*If given an argument, checks if it is a variable in env or exp
and deletes that node*/
int	cmd_unset(t_data *data, char **tokens, int tok)
{
	if (!tokens[tok + 1] || delim(tokens[tok + 1]))
		return (OK_EXIT);
	while (tokens[++tok])
	{
		if (delim(tokens[tok]))
			break ;
		if (!ft_isalpha(tokens[tok][0]) && tokens[tok][0] != '_')
		{
			printf("unset: '%c': not a valid identifier\n",
				tokens[tok][0]);
			continue ;
		}
		if ((tokens[tok][0] == '_' && !tokens[tok][1])
			|| check_unset(data, &data->env, tok)
			|| check_unset(data, &data->exp, tok))
			continue ;
	}
	return (OK_EXIT);
}
