/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 09:39:46 by gacorrei          #+#    #+#             */
/*   Updated: 2023/06/30 17:49:25 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Joins test to val if it exists after expanding variable
or if it is just text*/
char	*update_expansion(t_data *data, char *val, char *test)
{
	char	*temp;
	char	*temp_val;

	if (test[1] == '{')
		temp = find_var(data->env, test + 2);
	else if (!test[1] || test[1] == '\'' || test[1] == '\"')
		temp = 0;
	else if (test[1] == '?')
		temp = ft_itoa(update_exit_code(0, 0));
	else
		temp = find_var(data->env, test + 1);
	if (!temp)
		temp = ft_strdup("");
	temp_val = val;
	val = ft_strjoin(temp_val, temp);
	free(temp);
	free(test);
	free(temp_val);
	return (val);
}

/*Returns variable value, if it exists*/
char	*expansion(t_data *data, char *s)
{
	int		i;
	int		j;
	char	*test;
	char	*temp;
	char	*val;

	i = 0;
	val = ft_strdup("");
	while (s[i])
	{
		j = -1;
		while (s[i + ++j] && (s[i + j] != '$' || (s[i + j] == '$'
					&& (s[i + j + 1] == '$' || s[i + j + 1] == '}'))))
			continue ;
		if (j)
		{
			test = ft_substr(s, i, j);
			temp = val;
			val = ft_strjoin(temp, test);
			free(temp);
			free(test);
			i += j;
			continue ;
		}
		j = i + 1;
		while (s[j] && s[j] != '$' && s[j] != '}'
			&& s[j] != '\'' && s[j] != '\"' && j++)
			if (s[j - 1] == '?' && j == i + 2)
				break ;
		test = ft_substr(s, i, j - i);
		val = update_expansion(data, val, test);
		i = j;
		if (s[i] == '}')
			i++;
	}
	return (val);
}

/*Returns new string with text formatted without edge quotes*/
char	*quotes(char *str)
{
	int		len;
	char	*new;

	len = ft_strlen(str);
	new = ft_substr(str, 1, len - 2);
	free (str);
	return (new);
}

char	*token_parser(t_data *data, char *token)
{
	int		i;
	int		j;
	char	*new_token;
	char	*section;
	char	*temp;

	new_token = ft_strdup("");
	i = 0;
	while (token[i])
	{
		j = 0;
		while (token[i + ++j])
		{
			if (((token[i] == '\'' || token[i] == '\"')
					&& token[i + j] == token[i])
				|| token[i + j] == '\'' || token[i + j] == '\"')
				break ;
			continue ;
		}
		section = get_section(data, token, i, j);
		temp = new_token;
		new_token = ft_strjoin(temp, section);
		free(temp);
		free(section);
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
		data->tokens[i] = token_parser(data, data->tokens[i]);
		if (data->tokens[i][0] == '*' || char_finder(data->tokens[i], '*'))
			fix_tokens_wc(data, &i);
	}
	for (int i = 0; data->tokens[i]; i++)
		printf("Token %i: :%s:\n", i, data->tokens[i]);
	return (0);
}
