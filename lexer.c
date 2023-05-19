/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 09:09:44 by gacorrei          #+#    #+#             */
/*   Updated: 2023/05/19 12:23:04 by gacorrei         ###   ########.fr       */
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
	else if (c == ')' || c == '}')
		printf("Found unclosed parenthesis: %s\n", str);
	return (0);
}

/*Sets find value*/
void	get_find(char *str, char *find)
{
	if (str[0] == '\'' || str[0] == '\"')
		*find = str[0];
	else if (str[0] == '(')
		*find = ')';
	else if (str[0] == '{')
		*find = '}';
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
	j = 0;
	if (str[i] == '\'' || str[i] == '\"' || str[i] == '(' || str[i] == '{')
	{
		get_find(&str[i], &find);
		j = char_finder(&str[i], find);
		if (!j)
			return (0);
		/*CHECK ITERATIONS, SHOULD IT STAY ON I + J OR GO TO THE NEXT?*/
		i += j + 1;
		if (flag == 0)
			return (i);
		else
			return (j);
	}
	if (str[i] == ')' || str[i] == '}')
	{
		printf("Found unopened parenthesis: %s\n", str);
		return (0);
	}
	/*CHECK ITERATIONS, SHOULD IT STAY ON I + J OR GO TO THE NEXT?*/
	if (flag == 0)
		return (++i);
	else
		return (++j);
}

/*Checks for characters that should not be interpreted*/
int	forbidden(char *str)
{
	if (str[0] == '\\' || str[0] == ';' || str[0] == '[' || str[0] == ']'
		|| str[0] == '^' || str[0] == '#')
	{
		printf("Found forbidden character: %s\n", str);
		return (1);
	}
	return (0);
}

/*Checks if character is a delimiter*/
int	delim(char *str)
{
	if ((str[0] == '|' && str[1] != '|')
		|| (str[0] == '>' && str[1] != '>')
		|| (str[0] == '<' && str[1] != '<')
		|| str[0] == '$')
		return (1);
	if ((str[0] == '|' && str[1] == '|')
		|| (str[0] == '>' && str[1] == '>')
		|| (str[0] == '<' && str[1] == '<')
		|| (str[0] == '&' && str[1] == '&'))
		return (2);
	return (0);
}

int	other(char *str)
{
	if (forbidden(&str[0]))
		return (0);
	if (!ft_isspace(str[0]))
	/*NEEDS TO GO TO CORRECT PLACE, CAN'T GO 1 BY 1*/
		return (1);
	return (0);
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
			if (forbidden(&str[i]))
				return (-1);
			i = quote_case(str, i, 0);
			if (!i)
				return (-1);
			if (str[i - 1] == '\'' || str[i - 1] == '\"'
				|| str[i - 1] == ')' || str[i - 1] == '}')
				tok_num++;
		}
		if (!ft_isspace(str[i - 1]) && str[i - 1] != '\'' && str[i - 1] != '\"'
			&& str[i - 1] != ')' && str[i - 1] != '}')
			tok_num++;
	}
	return (tok_num);
}

/*FInds length of current token after determining its type*/
int	tok_len(char *str, int i)
{
	int	j;

	j = delim(&str[i]);
	if (j)
		return (j);
	j = quote_case(str, i, 1);
	if (j)
		return (j);
	j = other(&str[i]);
	if (j)
		return (j);
	return (0);
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
		j = tok_len(str, i);
		tokens[++k] = ft_substr(str, i, j);
		i += j + 1;
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
