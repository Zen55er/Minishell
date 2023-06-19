/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lexer3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 12:11:48 by gacorrei          #+#    #+#             */
/*   Updated: 2023/06/19 15:14:56 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Returns opposing character match.*/
char	get_match(char c)
{
	if (c == '(')
		return (')');
	if (c == '$')
		return ('}');
	return (c);
}

/*Adds new input from unclosed characters*/
void	update_input(char **input, char *extra)
{
	char	*temp;

	if (!extra)
		return ;
	temp = extra;
	extra = ft_substr(temp, 0, ft_strlen(temp) - 1);
	free(temp);
	temp = *input;
	*input = ft_strjoin(*input, extra);
	free(temp);
	free(extra);
}
