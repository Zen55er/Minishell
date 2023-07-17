/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 10:57:59 by gacorrei          #+#    #+#             */
/*   Updated: 2023/07/17 16:23:49 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Returns new string with text formatted without edge quotes*/
char	*quotes(t_data *data, char *str)
{
	int		len;
	char	*new;

	if (check_quotes_delimiter(str) && !data->quote_flag)
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

/*Combination of functions above for norminette reasons*/
void	quotes_delimiter_full(char **tokens, int tok)
{
	if (check_quotes_delimiter(tokens[tok]))
		quotes_delimiter(tokens, tok);
	return ;
}

/*Check to change quote_flag for parser quote cases.*/
int	exclude_delims(char *str)
{
	int	i;
	int	delims;
	int	extra;

	delims = 0;
	extra = 0;
	i = -1;
	while (str[++i])
	{
		while (str[i] == '\'' || str[i] == '\"')
			i++;
		if (!str[i])
			break ;
		if (delim(&str[i]))
			delims++;
		else
			extra++;
		if (delims > 1 || extra)
			return (1);
	}
	return (0);
}
