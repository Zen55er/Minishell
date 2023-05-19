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

	if (!tokens)
		return ;
	i = -1;
	while (tokens[++i])
	{
		if (tokens[i])
			free(tokens[i]);
	}
	free(tokens);
}
