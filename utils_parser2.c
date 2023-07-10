/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 10:57:59 by gacorrei          #+#    #+#             */
/*   Updated: 2023/07/10 11:17:16 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Returns new string with text formatted without edge quotes*/
char	*quotes(char *str)
{
	int		len;
	char	*new;

	if (check_quotes_delimiter(str))
		return (str);
	len = ft_strlen(str);
	new = ft_substr(str, 1, len - 2);
	free (str);
	return (new);
}

/*Checks if token is a delimiter with quotes*/
int	check_quotes_delimiter(char *token)
{
	char	*test;

	if (token[0] != '\'' && token[0] != '\"')
		return (0);
	test = ft_substr(token, 1, ft_strlen(token) - 2);
	if (delim_tok(test))
	{
		free(test);
		return (1);
	}
	free(test);
	return (0);
}

/*Replaces token with a new one without quotes*/
void	quotes_delimiter(char **tokens, int tok)
{
	char	*new_tok;

	new_tok = ft_substr(tokens[tok], 1, ft_strlen(tokens[tok]) - 2);
	free(tokens[tok]);
	tokens[tok] = new_tok;
	return ;
}
