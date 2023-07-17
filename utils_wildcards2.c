/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_wildcards2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 13:31:48 by gacorrei          #+#    #+#             */
/*   Updated: 2023/07/17 17:00:50 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Swaps nodes and updates temp positions*/
void	swap(t_ll **matches, t_ll **temp, t_ll **temp2, int flag)
{
	t_ll	*swap;

	swap = (*temp)->next;
	(*temp)->next = swap->next;
	swap->next = *temp;
	*temp = swap;
	if (!flag)
	{
		*matches = *temp;
		*temp2 = *temp;
	}
	else
	{
		(*temp2)->next = *temp;
		*temp = *matches;
		*temp2 = *matches;
	}
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
			swap(matches, &temp, &temp2, 0);
			continue ;
		}
		else if (temp->rank > temp->next->rank)
		{
			swap(matches, &temp, &temp2, 1);
			continue ;
		}
		temp = temp->next;
		if (temp != (*matches)->next)
			temp2 = temp2->next;
	}
}

/*Re-adds quotes to necessary tokens*/
void	reverse_delim_quotes(char **tokens, int tok)
{
	char	*new_tok;
	char	*temp;

	temp = ft_strdup("'");
	new_tok = ft_strjoin("'", tokens[tok]);
	new_tok = ft_strjoin_free(new_tok, temp);
	free(tokens[tok]);
	tokens[tok] = new_tok;
	return ;
}
