/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 09:09:44 by gacorrei          #+#    #+#             */
/*   Updated: 2023/06/21 09:44:07 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Checks for length of remaining characters, excluding forbidden values,
delimiters, quotes and parentheses.*/
int	other(char *str, int flag)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (!flag && forbidden(&str[i]))
			return (-1);
		if (!str[i] || ft_isspace(str[i]) || delim(&str[i], 0))
			break ;
		if (str[i] == '$' && str[i + 1] == '{')
		{
			i = special_dollar(str, flag);
			break ;
		}
		if (str[i] == '\'' || str[i] == '\"')
		{
			i = quote_case(&str[i]);
			break ;
		}
	}
	return (i);
}

/*Finds length of current token after determining its type*/
int	tok_len(char *str, int i, int flag)
{
	int	j;

	j = delim(&str[i], 0);
	if (j)
		return (j);
	j = other(&str[i], flag);
	return (j);
}

/*Counts tokens in input, accounts for delimiters, quotes and parentheses*/
int	count_tokens(t_data *data, char *str)
{
	int		i;
	int		j;
	int		tok_num;

	i = 0;
	tok_num = 0;
	while (str[i])
	{
		while (str[i] && ft_isspace(str[i]))
			i++;
		if (!str[i])
			break ;
		if (forbidden(str))
			return (0);
		if ((str[i] == '(' || str[i] == ')') && check_and_or(data, &str[i]))
			j = 1;
		else
			j = tok_len(str, i, 0);
		if (j < 0)
			return (0);
		tok_num++;
		i += j;
	}
	return (tok_num);
}

/*Places input tokens in 2d array for parser to analyse.
Ignores whitepaces between tokens*/
void	set_tokens(t_data *data, char **tokens, char *str)
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
		if (!str[i])
			break ;
		if ((str[i] == '(' || str[i] == ')') && check_and_or(data, &str[i]))
			j = 1;
		else
			j = tok_len(str, i, 1);
		if (!j && ++i)
			continue ;
		else
			tokens[++k] = ft_substr(str, i, j);
		i += j;
	}
	tokens[++k] = 0;
}

/*Calls functions to count and set tokens to send to parser.*/
char	**lexer(t_data *data, char **input)
{
	char	**tokens;
	int		tok_num;
	int		exit;

	exit = validate_input(input);
	if (exit)
	{
		update_exit_code(exit, 1);
		return (0);
	}
	tok_num = count_tokens(data, *input);
	if (tok_num <= 0)
		return (0);
	tokens = (char **)malloc(sizeof(char *) * (tok_num + 1));
	set_tokens(data, tokens, *input);
	for (int i = 0; tokens[i]; i++)
		printf("Token %i: :%s:\n", i, tokens[i]);
	return (tokens);
}
