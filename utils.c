/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 12:48:32 by gacorrei          #+#    #+#             */
/*   Updated: 2023/06/21 16:38:58 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*In cases where input for a command comes in a path (e.g. user/bin/ls),
returns only the end of the string (after the last '/).*/
char	*get_end_cmd(char *str)
{
	char	*cmd;
	int		i;

	i = -1;
	while (str[++i])
		continue ;
	while (str[--i] != '/')
		continue ;
	i++;
	cmd = ft_substr(str, i, ft_strlen(str) - i);
	return (cmd);
}

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
	return (ERROR_MISUSE);
}
