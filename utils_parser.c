/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 10:13:44 by gacorrei          #+#    #+#             */
/*   Updated: 2023/06/19 16:23:00 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Returns last exit code.*/
char	*get_exit_code(char *str1, char *str2)
{
	free(str1);
	free(str2);
	return (ft_itoa(g_exit_val));
}

char	*get_section(t_data *data, char *str, int i, int j)
{
	char	*section;

	if (str[i] == '\'' || str[i] == '\"' )
		section = quotes(data, ft_substr(str, i, j + 1));
	else
		section = ft_substr(str, i, j);
	return (section);
}

void	fix_tokens_wc(t_data *data, int *i)
{
	t_ll	*matches;

	matches = expand_wildcards(data->tokens[*i]);
	if (matches && list_size(matches) == 1)
	{
		free(data->tokens[*i]);
		data->tokens[*i] = ft_strdup(matches->var);
	}
	else if ((matches && list_size(matches) > 1))
		*i += add_tokens(data, matches, *i);
	free_list(&matches);
}

/*Checks if the two consecutive delimiters are allowed*/
int	check_consecutive(char *tok1, char *tok2)
{
	if (!ft_strncmp(tok1, tok2, 2)
		|| !ft_strncmp(tok1, ">>", 2) || !ft_strncmp(tok1, "<<", 2)
		|| !ft_strncmp(tok1, ">", 2) || !ft_strncmp(tok1, "<", 2)
		|| ((!ft_strncmp(tok1, "|", 2) || !ft_strncmp(tok1, "||", 2)
				|| !ft_strncmp(tok1, "&&", 2))
			&& (!ft_strncmp(tok2, "|", 2) || !ft_strncmp(tok2, "||", 2)
				|| !ft_strncmp(tok2, "&&", 2))))
		return (syntax_error(tok2));
	return (0);
}

/*If the current and next tokens are delimiters,
calls check_consecutive to validate them.*/
int	validate_tokens(char **tokens)
{
	int	i;

	i = -1;
	while (tokens[++i + 1])
	{
		if (delim(tokens[i], 1) && delim(tokens[i + 1], 1)
			&& check_consecutive(tokens[i], tokens[i + 1]))
			return (1);
	}
	return (0);
}
