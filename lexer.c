/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatrao <mpatrao@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 09:09:44 by gacorrei          #+#    #+#             */
/*   Updated: 2023/07/15 17:20:34 by mpatrao          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Checks for length of remaining characters.*/
int	other(char *str)
{
	int	i;
	int	j;

	i = -1;
	while (str[++i])
	{
		j = 0;
		if (!str[i] || ft_isspace(str[i]) || delim(&str[i]))
			break ;
		else if (str[i] == '$' && str[i + 1] == '{')
			j = special_dollar(str);
		else if (str[i] == '\'' || str[i] == '\"')
			j = quote_case(&str[i]);
		if (j == -1)
			return (j);
		i += j;
		if (!str[i])
			break ;
	}
	return (i);
}

/*Finds length of current token after determining its type*/
int	tok_len(char *str, int i)
{
	int	j;

	j = delim(&str[i]);
	if (j)
		return (j);
	j = other(&str[i]);
	return (j);
}

/*Counts tokens in input, accounts for delimiters, quotes and parentheses*/
int	count_tokens(char *str)
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
		else
			j = tok_len(str, i);
		if (j < 0)
			return (0);
		tok_num++;
		i += j;
	}
	return (tok_num);
}

/*Places input tokens in 2d array for parser to analyze.
Ignores whitespaces between tokens*/
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
		if (!str[i])
			break ;
		else
			j = tok_len(str, i);
		if (!j && ++i)
			continue ;
		else
			tokens[++k] = ft_substr(str, i, j);
		i += j;
	}
	tokens[++k] = 0;
}

/*Calls functions to count and set tokens to send to parser.*/
int	lexer(t_data *data, char **input)
{
	int		tok_num;
	int		exit;

	exit = validate_input(input);
	if (exit)
	{
		update_exit_code(exit, 1);
		if (ft_strcmp(*input, "exit 2"))
		{
			free(*input);
			return (1);
		}
	}
	tok_num = count_tokens(*input);
	if (tok_num <= 0)
	{
		free(*input);
		update_exit_code(1, 1);
		return (1);
	}
	data->tokens = (char **)malloc(sizeof(char *) * (tok_num + 1));
	set_tokens(data->tokens, *input);
	free(*input);
	return (0);
}
