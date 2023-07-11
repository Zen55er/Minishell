/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 10:13:44 by gacorrei          #+#    #+#             */
/*   Updated: 2023/07/11 11:26:56 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Returns original string modified with any necessary dollar expansions and/or
without outer quotes.*/
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

/*Gets list of expanded wildcards and calls function to replace array of tokens
with new entries.*/
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

/*Needed for norminette.
Extra conditions for validate_tokens.*/
int	validate_tokens2(char **tokens, int i)
{
	if (tokens[i + 1] && delim_tok(tokens[i]) && delim_tok(tokens[i + 1])
		&& check_consecutive(tokens[i], tokens[i + 1]))
		return (1);
	if (i == 0 && (!ft_strcmp(tokens[i], "|")
			|| !ft_strcmp(tokens[i], "||")
			|| !ft_strcmp(tokens[i], "&&")))
		return (syntax_error(tokens[i]));
	else if (!tokens[i + 1] && (!ft_strcmp(tokens[i], ">")
			|| !ft_strcmp(tokens[i], "<")
			|| !ft_strcmp(tokens[i], ">>")
			|| !ft_strcmp(tokens[i], "<<")))
		return (syntax_error("newline"));
	return (0);
}

/*If the current and next tokens are delimiters,
calls check_consecutive to validate them.*/
int	validate_tokens(char **tokens)
{
	int	i;
	int	flag;

	i = -1;
	flag = 0;
	while (tokens[++i])
	{
		if (!ft_strcmp(tokens[i], "("))
		{
			if (i > 0 && !delim_tok(tokens[i - 1]))
				return (syntax_error(tokens[i]));
			flag++;
		}
		if (!ft_strcmp(tokens[i], ")") && !flag)
			return (syntax_error(tokens[i]));
		else if (!ft_strcmp(tokens[i], ")") && flag)
			flag--;
		if (validate_tokens2(tokens, i))
			return (1);
	}
	return (0);
}
