/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 09:09:44 by gacorrei          #+#    #+#             */
/*   Updated: 2023/05/18 11:18:09 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Looks for c in str, if found returns how far from the start it is.
If the char is not found, prints error message.*/
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

/*If str[i] is a quote or parenthesis, calls char_finder to check
if it is closed correctly. Also checks for unopened parenthesis.
If str[i] is none off the above simply increments i.
With flag 0 returns i for main iterator (calls from count_tokens),
with flag 1 returns j for distance from start (calls from set_tokens)*/
int	quote_case(char *str, int i, int flag)
{
	int		j;
	char	find;

	find = 0;
	if (str[i] == '\'' || str[i] == '\"' || str[i] == '(')
	{
		if (str[i] == '\'' || str[i] == '\"')
			find = str[i];
		else if (str[i] == '(')
			find = ')';
		j = char_finder(&str[i], find);
		if (!j)
			return (0);
		i += j + 1;
		if (flag == 0)
			return (i);
		else
			return (j);
	}
	if (str[i] == ')')
	{
		printf("Found unopened parenthesis: %s\n", str);
		return (-1);
	}
	return (++i);
}

/*Counts tokens in input, taking into account quotes and parentheses*/
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
			i = quote_case(str, i, 0);
			if (!i)
				return (-1);
			if (str[i - 1] == '\'' || str[i - 1] == '\"' || str[i - 1] == ')')
				tok_num++;
		}
		if (!ft_isspace(str[i - 1]) && str[i - 1] != '\'' && str[i - 1] != '\"'
			&& str[i - 1] != ')')
			tok_num++;
	}
	return (tok_num);
}

/*Places input tokens in 2d array for parser to analyse.
Ignores whitepaces between tokens*/
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

/*Calls functions to count and set tokens to send to parser.*/
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
