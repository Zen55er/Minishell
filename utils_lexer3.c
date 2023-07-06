/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lexer3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 12:11:48 by gacorrei          #+#    #+#             */
/*   Updated: 2023/07/06 15:01:37 by gacorrei         ###   ########.fr       */
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

/*Returns new string with text formatted without edge quotes*/
char	*quotes(char *str)
{
	int		len;
	char	*new;

	len = ft_strlen(str);
	new = ft_substr(str, 1, len - 2);
	free (str);
	return (new);
}
