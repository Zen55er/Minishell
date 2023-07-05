/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 17:50:53 by gacorrei          #+#    #+#             */
/*   Updated: 2023/07/05 08:50:38 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Looks for c in str, if found returns how far from the start it is.
If the char is not found, prints error message.*/
int	char_finder(char *str, char c)
{
	int	i;

	if (!str || !str[0])
		return (0);
	i = 0;
	while (str[++i])
	{
		if (str[i] == c)
			return (i);
	}
	if (str[0] == c && (c == '\'' || c == '\"'))
		printf("Found unclosed quotes: %s\n", str);
	return (0);
}

/*Checks for characters that should not be interpreted*/
int	forbidden(char *str)
{
	if (str[0] == '\\' || str[0] == '[' || str[0] == ']'
		|| str[0] == ';' || str[0] == '^' || str[0] == '#'
		|| str[0] == '`'
		|| (str[0] == '(' && str[1] == ')')
		|| (str[0] == '<' && str[1] == '(')
		|| (str[0] == '$' && str[1] == '(')
		|| (str[0] == ')' && str[1] == '$')
		|| (str[0] == '&' && str[1] != '&'))
	{
		printf("Found forbidden character or character combination: %s\n", str);
		return (1);
	}
	return (0);
}

/*Checks if character is a delimiter.
When running executer (flag == 1), 
avoids parenthesis from logical operator cases*/
int	delim(char *str)
{
	if (!str)
		return (0);
	if ((str[0] == '|' && str[1] != '|')
		|| (str[0] == '>' && str[1] != '>')
		|| (str[0] == '<' && str[1] != '<')
		|| str[0] == '(' || str[0] == ')')
		return (1);
	if ((str[0] == '|' && str[1] == '|')
		|| (str[0] == '>' && str[1] == '>')
		|| (str[0] == '<' && str[1] == '<')
		|| (str[0] == '&' && str[1] == '&'))
		return (2);
	return (0);
}

/*If str[i] is a quote, calls char_finder to check
if it is closed correctly.*/
int	quote_case(char *str)
{
	int		j;
	char	find;

	find = 0;
	j = 0;
	if (str[0] == '\'')
		find = '\'';
	else
		find = '\"';
	j = char_finder(str, find);
	if (!j)
		return (-1);
	return (j);
}

int	special_dollar(char *str)
{
	int		bad_sub;
	int		found;
	int		i;

	bad_sub = 0;
	found = 0;
	i = -1;
	while (str[++i])
	{
		if (ft_isspace(str[i]) && !found)
			bad_sub = i;
		if (str[i] == '}')
			found = i;
		if (found && str[i] == '{')
			found = 0;
	}
	if (found && bad_sub)
		return (bad_substitution(str, found + 1));
	else if (bad_sub)
		return (bad_sub);
	return (i);
}
