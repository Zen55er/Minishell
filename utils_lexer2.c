/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lexer2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 15:31:01 by gacorrei          #+#    #+#             */
/*   Updated: 2023/07/10 11:20:47 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Requests extra input from user and updates input string*/
int	missing_input(char **input, char match)
{
	char	*temp;
	char	*extra;

	signal_input();
	extra = ft_strdup(" ");
	while (1)
	{
		write(STDOUT_FILENO, "> ", 2);
		temp = get_next_line(STDIN_FILENO);
		if (!temp)
			break ;
		if (temp[0] == '\n' && int_free(temp, 1))
			continue ;
		extra = ft_strjoin_free(extra, temp);
		if (extra[0] == match || char_finder(extra, match))
			break ;
	}
	if (extra[0] != match && !char_finder(extra, match) && int_free(extra, 1))
		return (unexpected_eof(input, match));
	update_input(input, extra);
	signal_global();
	return (0);
}

/*If input ends in |, || or &&, calls missing input to complete it.*/
int	check_end(char **input, int i)
{
	if ((*input)[i] == '|' && (*input)[i + 1] != '|')
		i++;
	if ((*input)[i] == '|' && (*input)[i + 1] == '|')
		i += 2;
	if ((*input)[i] == '&' && (*input)[i + 1] == '&')
		i += 2;
	while ((*input)[i] && ft_isspace((*input)[i]))
		i++;
	if (!(*input)[i])
		return (missing_input(input, '\n'));
	return (0);
}

/*Returns index of next matching quote (or end of str).
If there is no matching quote and the string ends, returns the index
of the previous character to avoid a heap overflow in validate_input.*/
int	jump_quotes(char *str, int i, char quote)
{
	while (str[++i] && str[i] != quote)
		continue ;
	if (!str[i])
		return (i - 1);
	return (i);
}

/*Checks whether input is complete
(no missing information after |, ||, && or ${).*/
int	validate_input(char **str)
{
	int		i;
	int		exit;
	char	match;

	exit = 0;
	i = -1;
	while ((*str)[++i])
	{
		if ((*str)[i] == '\'' || (*str)[i] == '\"')
			i = jump_quotes(*str, i, (*str)[i]);
		if (forbidden((*str), i))
			return (1);
		else if ((*str)[i] == '(' || ((*str)[i] == '$' && (*str)[i + 1] == '{'))
		{
			match = get_match((*str)[i]);
			if (!char_finder(*str, match))
				exit = missing_input(str, match);
			i += char_finder(*str + i, (*str)[i]);
		}
		else if (i && ((*str)[i] == '|' || (*str)[i] == '&'))
			exit = check_end(str, i);
		if (exit || !ft_strcmp(*str, "exit 2"))
			return (exit);
	}
	return (0);
}
