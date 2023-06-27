/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 09:39:46 by gacorrei          #+#    #+#             */
/*   Updated: 2023/06/26 14:00:33 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Joins test to val if it exists after expanding variable
or if it is just text*/
char	*update_expansion(t_data *data, char *val, char *test)
{
	char	*temp;
	char	*temp_val;

	/* if (!ft_strcmp(test, "$?"))
		return (get_exit_code(val, test)); */
	if (test[0] == '$')
	{
		if (test[1] == '{')
			temp = find_var(data->env, test + 2);
		else if (test[1] == '?')
			temp = ft_itoa(update_exit_code(0, 0));
		else
			temp = find_var(data->env, test + 1);
		if (!temp)
			temp = ft_strdup("");
		temp_val = val;
		val = ft_strjoin(temp_val, temp);
		free(temp);
	}
	else
	{
		temp_val = val;
		val = ft_strjoin(temp_val, test);
	}
	free(test);
	free(temp_val);
	return (val);
}

/*Returns variable value, if it exists*/
char	*expansion(t_data *data, char	*s)
{
	int		i;
	int		j;
	char	*test;
	char	*val;

	i = 0;
	val = ft_strdup("");
	while (s[i])
	{
		j = i;
		if (s[i] == '$')
			j++;
		while (s[j] && s[j] != '$' && s[j] != '}'
			&& s[j] != '\'' && s[j] != '\"')
		{
			j++;
			if (s[j - 1] == '?' && j == i + 2)
				break ;
		}
		if (j == i && s[j] && s[j] != '}' && s[j] != '\'' && s[j] != '\"')
			j++;
		test = ft_substr(s, i, j - i);
		val = update_expansion(data, val, test);
		i = j;
		if (s[i] == '}')
			i++;
	}
	free(s);
	return (val);
}

/*Returns new string with text formatted according to quote type*/
char	*quotes(t_data *data, char *str)
{
	int		len;
	int		flag;
	char	*new;
	char	*expand_new;

	flag = 0;
	if (str[0] == '\"')
		flag = 1;
	len = ft_strlen(str);
	new = ft_substr(str, 1, len - 2);
	free (str);
	if (flag && (new[0] == '$' || char_finder(new, '$')))
	{
		expand_new = expansion(data, new);
		return (expand_new);
	}
	return (new);
}

/*Iterates through string to remove quotes and expand variables*/
char	*quote_str(t_data *data, char *str)
{
	char	*new;
	char	*section;
	char	*temp;
	int		i;
	int		j;

	i = 0;
	new = ft_strdup("");
	while (str[i])
	{
		j = 0;
		while (str[i + ++j] && str[i + j] != str[i])
			continue ;
		section = get_section(data, str, i, j);
		temp = new;
		new = ft_strjoin(new, section);
		free(temp);
		free(section);
		if (str[i] == '\'' || str[i] == '\"' )
			j++;
		i += j;
	}
	free(str);
	return (new);
}

/*Parses cases with $ and quotes*/
int	parser(t_data	*data)
{
	int		i;

	if (validate_tokens(data, data->tokens))
		return (1);
	i = -1;
	while (data->tokens[++i])
	{
		if (data->tokens[i][0] == '\'' || data->tokens[i][0] == '\"'
			|| char_finder(data->tokens[i], '\'')
			|| char_finder(data->tokens[i], '\"'))
			data->tokens[i] = quote_str(data, data->tokens[i]);
		else if (data->tokens[i][0] == '$'
			|| char_finder(data->tokens[i], '$'))
			data->tokens[i] = expansion(data, data->tokens[i]);
		else if (data->tokens[i][0] == '*'
			|| char_finder(data->tokens[i], '*'))
			fix_tokens_wc(data, &i);
	}
	// for (int i = 0; data->tokens[i]; i++)
	// 	printf("Token %i: :%s:\n", i, data->tokens[i]);
	return (0);
}
