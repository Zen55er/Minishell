/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 09:09:44 by gacorrei          #+#    #+#             */
/*   Updated: 2023/05/17 12:26:04 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_space(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	return (i);
}

int	quote_finder(char *str)
{
	int	i;
	int	quote;

	i = 0;
	quote = str[i];
	while (str[++i])
	{
		if (str[i] == quote)
			return (i);
	}
	printf("Found unclosed quotes: %s\n", str);
	return (0);
}

int	count_tokens(char *str)
{
	int		i;
	int		j;
	int		tok_num;

	i = 0;
	tok_num = 0;
	while (str[i])
	{
		i += skip_space(&str[i]);
		while (str[i] && !ft_isspace(str[i]))
		{
			if (str[i] == '\'' || str[i] == '\"')
			{
				j = quote_finder(&str[i]);
				if (!j)
					return (-1);
				if (j > 1)
					tok_num++;
				i += j;
			}
			i++;
		}
		if (!ft_isspace(str[i - 1]) && str[i - 1] != '\'' && str[i - 1] != '\"')
			tok_num++;
	}
	return (tok_num);
}

void	set_tokens(char **tokens, char *str)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	k = -1;
	while (str[i])
	{
		while (str[i] && ft_isspace(str[i]))
			i++;
		if (str[i] == '\'' || str[i] == '\"')
		{
			j = quote_finder(&str[i]);
			tokens[++k] = ft_substr(str, i, j + 1);
			i += j + 1;
		}
		j = 0;
		while (str[i + j] && !ft_isspace(str[i + j]))
			j++;
		if (!j)
			continue ;
		tokens[++k] = ft_substr(str, i, j);
		i += j;
	}
	tokens[++k] = 0;
}

char	**lexer(char *input)
{
	char	**tokens;
	int		i;
	int		tok_num;

	i = -1;
	tok_num = count_tokens(input);
	if (tok_num <= 0)
		return (0);
	tokens = (char **)malloc(sizeof(char *) * (tok_num + 1));
	set_tokens(tokens, input);
	for (int i = 0; tokens[i]; i++)
		printf("Token %i: :%s:\n", i, tokens[i]);
	return (tokens);
}