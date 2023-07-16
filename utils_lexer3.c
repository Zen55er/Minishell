/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lexer3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 12:11:48 by gacorrei          #+#    #+#             */
/*   Updated: 2023/07/10 11:01:27 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Returns opposing character match.*/
char	get_match(char c)
{
	if (c == '(')
		return (')');
	if (c == '$')
		return ('}');
	return (c);
}

/*Adds new input from unclosed characters*/
void	update_input(char **input, char *extra)
{
	char	*temp;

	if (!extra)
		return ;
	temp = extra;
	extra = ft_substr(temp, 0, ft_strlen(temp) - 1);
	free(temp);
	temp = *input;
	*input = ft_strjoin(*input, extra);
	free(temp);
	free(extra);
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

/*Checks if final characters are && or || to call check end in validate input.
Needed for norm.*/
int	check_end_chars(char *str, int i)
{
	if ((str[i] == '|' && str[i - 1] == '|') || str[i] == '&')
		return (1);
	return (0);
}
