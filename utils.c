/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 12:48:32 by gacorrei          #+#    #+#             */
/*   Updated: 2023/05/19 13:09:11 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Frees lexer tokens*/
void	free_tokens(char **tokens)
{
	int	i;

	i = -1;
	while (tokens[++i])
	{
		if (tokens[i])
			free(tokens[i]);
	}
	free(tokens);
}

void	free_all(char *input, char *input2, char **tokens)
{
	if (input)
		free(input);
	if (input2)
		free(input2);
	if (tokens)
		free_tokens(tokens);
	return ;
}
