/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lexer2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 15:31:01 by gacorrei          #+#    #+#             */
/*   Updated: 2023/06/22 08:37:10 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Requests extra input from user and updates input string*/
int	missing_input(char **input, char match)
{
	char	*temp;
	char	*temp_extra;
	char	*extra;

	extra = ft_strdup(" ");
	while (1)
	{
		write(STDOUT_FILENO, "> ", 2);
		temp = get_next_line(STDIN_FILENO);
		if (!temp)
			break ;
		temp_extra = extra;
		extra = ft_strjoin(extra, temp);
		free(temp);
		free(temp_extra);
		if (extra[0] == match || char_finder(extra, match))
			break ;
	}
	if (extra[0] != match && !char_finder(extra, match))
	{
		free(extra);
		return (unexpected_eof(match));
	}
	update_input(input, extra);
	return (0);
}

/*If input ends in |, || or &&, calls missing input to complete it.*/
int	check_end(char **input, int i)
{
	if ((*input)[i] == '|' && (*input)[i] != '|')
		i++;
	if ((*input)[i] == '|' && (*input)[i] == '|')
		i += 2;
	if ((*input)[i] == '&' && (*input)[i] == '&')
		i += 2;
	while ((*input)[i] && ft_isspace((*input)[i]))
		i++;
	if (!(*input)[i])
		return (missing_input(input, '\n'));
	return (0);
}

/*Checks whether input is complete
(no missing information after |, ||, && or ${).*/
int	validate_input(char **input)
{
	int		i;
	int		exit;
	char	match;

	exit = 0;
	i = -1;
	while ((*input)[++i])
	{
		if ((*input)[i] == '\'' || (*input)[i] == '\"' || (*input)[i] == '('
		|| ((*input)[i] == '$' && (*input)[i + 1] == '{'))
		{
			match = get_match((*input)[i]);
			exit = missing_input(input, match);
			i += char_finder(*input + i, (*input)[i]);
		}
		else if (((*input)[i] == '|' || (*input)[i] == '&'))
			exit = check_end(input, i);
		if (exit)
			return (exit);
	}
	return (0);
}
