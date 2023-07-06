/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 09:39:46 by gacorrei          #+#    #+#             */
/*   Updated: 2023/07/06 15:01:34 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Joins test to val if it exists after expanding variable
or if it is just text*/
char	*update_expansion(t_data *data, char *val, char *test)
{
	char	*temp;
	char	*new_val;

	if (test[1] == '{')
		temp = find_var(data->env, test + 2);
	else if (!test[1])
		temp = ft_strdup("$");
	else if (!test[1] || test[1] == '\'' || test[1] == '\"')
		temp = 0;
	else if (test[1] == '?')
		temp = ft_itoa(update_exit_code(0, 0));
	else
		temp = find_var(data->env, test + 1);
	if (!temp)
		temp = ft_strdup("");
	new_val = ft_strjoin(val, temp);
	free(temp);
	free(test);
	free(val);
	return (new_val);
}

/*Needed for norm in expansion function.
Updates val string and i.*/
int	expansion_join(char	**val, char *s, int *i, int *j)
{
	*val = ft_strjoin_free(*val, ft_substr(s, *i, *j));
	*i += *j;
	return (1);
}

/*Returns variable value, if it exists*/
char	*expansion(t_data *data, char *s)
{
	int		i;
	int		j;
	char	*val;

	i = 0;
	val = ft_strdup("");
	while (s[i])
	{
		j = -1;
		while (s[i + ++j] && (s[i + j] != '$' || (s[i + j] == '$'
					&& (s[i + j + 1] == '$' || s[i + j + 1] == '}'))))
			continue ;
		if (j && expansion_join(&val, s, &i, &j))
			continue ;
		j = i + 1;
		while (s[j] && s[j] != '$' && s[j] != '}' && s[j] != '\'' && s[j] != ' '
			&& s[j] != '\"' && j++)
			if (s[j - 1] == '?' && j == i + 2)
				break ;
		val = update_expansion(data, val, ft_substr(s, i, j - i));
		i = j;
		if (s[i] == '}')
			i++;
	}
	return (val);
}

char	*token_parser(t_data *data, char *token)
{
	int		i;
	int		j;
	char	*new_token;

	new_token = ft_strdup("");
	i = 0;
	while (token[i])
	{
		j = 0;
		while (token[i + ++j])
		{
			if (((token[i] == '\'' || token[i] == '\"')
					&& token[i + j] == token[i])
				|| (token[i] != '\'' && token[i] != '\"'
					&& (token[i + j] == '\'' || token[i + j] == '\"')))
				break ;
			continue ;
		}
		new_token = ft_strjoin_free(new_token, get_section(data, token, i, j));
		if (token[i] == '\'' || token[i] == '\"')
			j++;
		i += j;
	}
	free(token);
	return (new_token);
}

/*Parses cases with $, quotes and wildcards*/
int	parser(t_data	*data)
{
	int		i;

	if (validate_tokens(data, data->tokens))
		return (1);
	i = -1;
	while (data->tokens[++i])
	{
		if (data->tokens[i][0] == '*' || char_finder(data->tokens[i], '*'))
			fix_tokens_wc(data, &i);
		data->tokens[i] = token_parser(data, data->tokens[i]);
	}
	// for (int i = 0; data->tokens[i]; i++)
	// 	printf("Token %i: :%s:\n", i, data->tokens[i]);
	return (0);
}
