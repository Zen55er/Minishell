/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 12:48:32 by gacorrei          #+#    #+#             */
/*   Updated: 2023/06/23 10:28:18 by gacorrei         ###   ########.fr       */
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

/*Error message for ${VAR} cases.*/
int	bad_substitution(char *str, int end)
{
	char	*temp;

	temp = ft_substr(str, 0, end);
	printf("minishell: %s: bad substitution\n", temp);
	free(temp);
	return (-1);
}

/*Error message for token validation.*/
int	syntax_error(char *str)
{
	printf("minishell: syntax error near unexpected token `%s'\n", str);
	return (1);
}

/*Error message for missing input cases.
When CTRL+D is used to cancel missing input cases the program must exit if
match is newline (replaces input with exit 2 to exit minishell),
otherwise minishell does not exit and the prompt will be updated.*/
int	unexpected_eof(char **input, char c)
{
	if (c == '\n')
	{
		printf("minishell: syntax error: unexpected end of file\n");
		free (*input);
		*input = (char *)malloc(sizeof(char) * 7);
		ft_strlcpy(*input, "exit 2", 7);
		return (0);
	}
	else
	{
		printf("minishell: unexpected EOF while looking for matching`%c'\n", c);
		printf("minishell: syntax error: unexpected end of file\n");
	}
	return (ERROR_MISUSE);
}

unsigned long long	ft_atoull(const char *nptr)
{
	int					i;
	unsigned long long	final;

	i = -1;
	final = 0;
	while (ft_isdigit(nptr[++i]))
		final = final * 10 + (nptr[i] - '0');
	return (final);
}
