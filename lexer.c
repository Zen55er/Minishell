/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 09:09:44 by gacorrei          #+#    #+#             */
/*   Updated: 2023/05/18 16:10:27 by gacorrei         ###   ########.fr       */
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

/*Places input tokens in 2d array for parser to analyse.
Ignores whitepaces between tokens*/
/* void	set_tokens(char **tokens, char *s)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	k = -1;
	while (s[i])
	{
		while (s[i] && ft_isspace(s[i]))
			i++;
		while (s[i] == '\'' || s[i] == '\"' || s[i] == '(' || s[i] == '}')
		{
			j = quote_case(s, i, 1);
			tokens[++k] = ft_substr(s, i, j + 1);
			i += j + 1;
		}
		j = 0;
		while (s[i + j] && !ft_isspace(s[i + j]))
			j++;
		if (j)
		{
			tokens[++k] = ft_substr(s, i, j);
			i += j;
		}
	}
	tokens[++k] = 0;
} */

int	delim(char *str)
{
	int	i;

	i = 0;
	/*CHECK FOR FUNCTIONS IN LIBFT THAT DO THIS*/
	if ((str[i] == '|' && str[i + 1] != '|')
		|| (str[i] == '>' && str[i + 1] != '>')
		|| (str[i] == '<' && str[i + 1] != '<')
		|| str[i] == '$')
		return (1);
	if ((str[i] == '|' && str[i + 1] == '|')
		|| (str[i] == '>' && str[i + 1] == '>')
		|| (str[i] == '<' && str[i + 1] == '<'))
		return (2);
	return (0);
}

void	set_tokens(char **tokens, char *s)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	k = -1;
	while (s[i])
	{
		while (s[i] && ft_isspace(s[i]))
			i++;
		while (s[i + j] && !ft_isspace(s[i + j]))
		{
			/*CHECK THIS!!!*/
			j = delim(&s[i]);
			if (j)
			{
				tokens[++k] = ft_substr(s, i, j);
				continue ;
			}
			else
			{
				j = quote_case(&s[i], i, 1);
				tokens[++k] = ft_substr(s, i, j);
			}
			i += j + 1;
		}
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
