/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 09:09:44 by gacorrei          #+#    #+#             */
/*   Updated: 2023/05/18 10:55:13 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	char_finder(char *str, char c)
{
	int	i;

	i = 0;
	while (str[++i])
	{
		if (str[i] == c)
			return (i);
	}
	if (c == '\'' || c == '\"')
		printf("Found unclosed quotes: %s\n", str);
	else if (c == ')')
		printf("Found unclosed parenthesis: %s\n", str);
	return (0);
}

int	quote_case(char *str, int i, int flag)
{
	int	j;

	if (str[i] == '\'' || str[i] == '\"')
	{
		j = char_finder(&str[i], str[i]);
		if (!j)
			return (0);
		i += j + 1;
		if (flag == 0)
			return (i);
		else
			return (j);
	}
	if (str[i] == '(')
	{
		j = char_finder(&str[i], ')');
		if (!j)
			return (0);
		i += j + 1;
		if (flag == 0)
			return (i);
		else
			return (j);
	}
	return (++i);
}

int	count_tokens(char *str)
{
	int		i;
	int		tok_num;

	i = 0;
	tok_num = 0;
	while (str[i])
	{
		while (str[i] && ft_isspace(str[i]))
			i++;
		while (str[i] && !ft_isspace(str[i]))
		{
			if (str[i] == ')')
			{
				printf("Found unopened parenthesis: %s\n", str);
				return (-1);
			}
			i = quote_case(str, i, 0);
			if (!i)
				return (-1);
			if (str[i - 1] == '\'' || str[i - 1] == '\"' || str[i - 1] == ')')
				tok_num++;
		}
		if (!ft_isspace(str[i - 1]) && str[i - 1] != '\'' && str[i - 1] != '\"' && str[i - 1] != ')')
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
		while (str[i] == '\'' || str[i] == '\"' || str[i] == '(')
		{
			j = quote_case(str, i, 1);
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
