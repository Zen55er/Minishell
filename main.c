/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 14:25:04 by gacorrei          #+#    #+#             */
/*   Updated: 2023/05/17 11:33:10 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*input;
	char	**tokens;

	tokens = 0;
	signal_global();
	while (1)
	{
		input = readline("minishell> ");
		if (!input)
			break ;
		tokens = lexer(input);
		free_tokens(tokens);
		tokens = 0;
		free(input);
	}
	free_tokens(tokens);
	return (0);
}
