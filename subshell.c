/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 17:55:19 by gacorrei          #+#    #+#             */
/*   Updated: 2023/06/24 19:44:43 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Copies tokens that are inside parentheses and sends them to executor.*/
void	subshell(t_data *data, int *token)
{
	int		i;
	int		j;

	i = 0;
	j = *token;
	while (data->tokens[++j] && smart_compare(data->tokens[j], ")"))
		i++;
	data->sub_tokens = (char **)malloc(sizeof(char *) * (i + 1));
	if (!data->sub_tokens)
		return ;
	i = -1;
	while (data->tokens[++(*token)] && smart_compare(data->tokens[*token], ")"))
		data->sub_tokens[++i] = data->tokens[*token];
	data->sub_tokens[++i] = 0;
	for (int j = 0; data->sub_tokens[j]; j++)
		printf("Token %i: :%s:\n", j, data->sub_tokens[j]);
	executor(data, data->sub_tokens);
	return ;
}
