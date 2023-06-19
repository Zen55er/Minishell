/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lexer2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 15:31:01 by gacorrei          #+#    #+#             */
/*   Updated: 2023/06/19 15:15:09 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bad_substitution(char *str, int end)
{
	char	*temp;

	temp = ft_substr(str, 0, end);
	printf("minishell: %s: bad substitution\n", temp);
	free(temp);
	return (-1);
}

int	syntax_error(char *str)
{
	printf("minishell: syntax error near unexpected token `%s'\n", str);
	return (1);
}

int	unexpected_eof(char c)
{
	printf("minishell: unexpected EOF while looking for matching`%c'\n", c);
	printf("minishell: syntax error: unexpected end of file\n");
	return (ERROR_SYNTAX);
}

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

int	validate_input(char **input)
{
	int		i;
	int		exit;
	char	match;

	/*DO UNEXPECTED TOKENS*/
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
		if (exit)
			return (exit);
	}
	return (0);
}
