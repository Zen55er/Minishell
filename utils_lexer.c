/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 17:50:53 by gacorrei          #+#    #+#             */
/*   Updated: 2023/06/12 13:12:42 by gacorrei         ###   ########.fr       */
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

/*Checks for characters that should not be interpreted*/
int	forbidden(char *str)
{
	if (str[0] == '\\' || str[0] == '[' || str[0] == ']'
		|| str[0] == ';' || str[0] == '^' || str[0] == '#'
		|| (str[0] == '(' && str[1] == '(')
		|| (str[0] == ')' && str[1] == ')')
		|| (str[0] == '<' && str[1] == '(')
		|| (str[0] == '$' && str[1] == '(')
		|| (str[0] == ')' && str[1] == '$'))
	{
		printf("Found forbidden character(s): %s\n", str);
		return (1);
	}
	return (0);
}

/*Checks if character is a delimiter.
When running executer (flag == 1), 
avoids pasrenthesis from logical operator cases*/
int	delim(char *str, int flag)
{
	if (flag && (str[0] == '(' || str[0] == ')') && !str[1])
		return (1);
	if ((str[0] == '|' && str[1] != '|')
		|| (str[0] == '>' && str[1] != '>')
		|| (str[0] == '<' && str[1] != '<'))
		return (1);
	if ((str[0] == '|' && str[1] == '|')
		|| (str[0] == '>' && str[1] == '>')
		|| (str[0] == '<' && str[1] == '<')
		|| (str[0] == '&' && str[1] == '&'))
		return (2);
	return (0);
}

/*If str[i] is a quote or parenthesis, calls char_finder to check
if it is closed correctly. Also checks for unopened parenthesis.*/
int	quote_case(char *str)
{
	int		j;
	char	find;

	find = 0;
	j = 0;
	if (str[0] == '\'' || str[0] == '\"' || str[0] == '(' || str[0] == '{')
	{
		get_find(str, &find);
		j = char_finder(str, find);
		if (!j)
			return (-1);
		return (++j);
	}
	if (str[0] == ')' || str[0] == '}')
	{
		printf("Found unopened parenthesis: %s\n", str);
		return (-1);
	}
	return (0);
}
