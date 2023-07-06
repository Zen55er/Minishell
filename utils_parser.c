/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 10:13:44 by gacorrei          #+#    #+#             */
/*   Updated: 2023/07/06 15:07:31 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_section(t_data *data, char *str, int i, int j)
{
	char	*section;
	char	*temp;

	if (str[i] == '\'' || str[i] == '\"' )
		section = ft_substr(str, i, j + 1);
	else
		section = ft_substr(str, i, j);
	if (section[0] != '\'' && (section[0] == '$' || char_finder(section, '$')))
	{
		temp = section;
		section = expansion(data, section);
		free(temp);
	}
	if (section[0] == '\'' || section[0] == '\"')
		section = quotes(section);
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
	if ((!ft_strcmp(tok1, tok2) && ft_strcmp(tok1, "(") && ft_strcmp(tok1, ")"))
		|| !ft_strcmp(tok1, ">>") || !ft_strcmp(tok1, "<<")
		|| !ft_strcmp(tok1, ">") || !ft_strcmp(tok1, "<")
		|| ((!ft_strcmp(tok1, "|") || !ft_strcmp(tok1, "||")
				|| !ft_strcmp(tok1, "&&"))
			&& (!ft_strcmp(tok2, "|") || !ft_strcmp(tok2, "||")
				|| !ft_strcmp(tok2, "&&")))
		|| (!ft_strcmp(tok2, "(") && (!ft_strcmp(tok1, ">>")
				|| !ft_strcmp(tok1, "<<")
				|| !ft_strcmp(tok1, ">") || !ft_strcmp(tok1, "<"))))
		return (syntax_error(tok2));
	return (0);
}

/*If the current and next tokens are delimiters,
calls check_consecutive to validate them.*/
int	validate_tokens(t_data *data, char **tokens)
{
	int	i;
	int	flag;

	i = -1;
	flag = 0;
	while (tokens[++i])
	{
		if (!ft_strcmp(tokens[i], "("))
		{
			if (i > 0 && !delim(tokens[i - 1]))
				return (syntax_error(tokens[i]));
			if (!check_single_cmd(data, tokens[i + 1]))
				return (syntax_error(tokens[i + 1]));
			flag++;
		}
		if (!ft_strcmp(tokens[i], ")"))
		{
			if (!flag)
				return (syntax_error(tokens[i]));
			else
				flag--;
		}
		if (i == 0 && (!ft_strcmp(tokens[i], "|") || !ft_strcmp(tokens[i], "||")
				|| !ft_strcmp(tokens[i], "&&")))
			return (syntax_error(tokens[i]));
		else if (!tokens[i + 1] && (!ft_strcmp(tokens[i], ">")
				|| !ft_strcmp(tokens[i], "<") || !ft_strcmp(tokens[i], ">>")
				|| !ft_strcmp(tokens[i], "<<")))
			return (syntax_error("newline"));
		if (tokens[i + 1] && delim(tokens[i]) && delim(tokens[i + 1])
			&& check_consecutive(tokens[i], tokens[i + 1]))
			return (1);
	}
	return (0);
}
