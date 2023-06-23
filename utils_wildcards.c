/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_wildcards.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 11:12:34 by gacorrei          #+#    #+#             */
/*   Updated: 2023/06/11 12:30:49 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Needed for norminette in compare_wc.*/
void	double_increment(int *i, int *j)
{
	(*i)++;
	(*j)++;
	return ;
}

/*Needed for norminette in compare_wc.*/
void	found_wildcard(int *i, int *j, int *prev_wc, int *backtrack)
{
	(*i)++;
	*prev_wc = *i;
	*backtrack = *j;
	return ;
}

/*Needed for norminette in compare_wc.*/
void	return_to_previous(int *i, int *j, int *prev_wc, int *backtrack)
{
	*i = *prev_wc;
	*j = (*backtrack)++;
}

/*Needed for norminette in compare_wc.
Checks remaining chars of token (if any),
if any are different from '*', there is no match.*/
int	final_wc_check(int i, char *token)
{
	while (token[i])
	{
		if (token[i] != '*')
			return (0);
		i++;
	}
	return (1);
}
