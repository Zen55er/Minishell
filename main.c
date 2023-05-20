/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 14:25:04 by gacorrei          #+#    #+#             */
/*   Updated: 2023/05/19 09:39:30 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*input;
	char	*input2;
	char	**tokens;

	tokens = 0;
	signal_global();
	while (1)
	{
		input = readline("minishell> ");
		if (!input || !ft_strncmp(input, "exit", ft_strlen(input)))
			break ;
		input2 = ft_strtrim(input, " ");
		add_history(input2);
		tokens = lexer(input);
		free_all(input, input2, tokens);
		input2 = 0;
		tokens = 0;
	}
	free_all(input, input2, tokens);
	return (0);
}
