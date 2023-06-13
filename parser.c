/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 09:39:46 by gacorrei          #+#    #+#             */
/*   Updated: 2023/06/13 10:30:13 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Joins test to val if it exists after expanding variable
or if it is just text*/
char	*update_expansion(t_data *data, char *val, char **test)
{
	char	*temp;
	char	*temp_val;

	if (!ft_strncmp(*test, "$?", ft_strlen(*test)))
		return (get_exit_code(data, val, test));
	if (*test[0] == '$')
	{
		temp = find_var(data->env, *test + 1);
		if (!temp)
			temp = ft_strdup("");
		temp_val = val;
		val = ft_strjoin(temp_val, temp);
		free(temp);
	}
	else
	{
		temp_val = val;
		val = ft_strjoin(temp_val, *test);
	}
	free(*test);
	free(temp_val);
	return (val);
}

/*Returns variable value, if it exists*/
char	*expansion(t_data *data, char	*str)
{
	int		i;
	int		j;
	char	*test;
	char	*val;

	i = 0;
	val = ft_strdup("");
	while (str[i])
	{
		j = i;
		if (str[i] == '$')
			j++;
		while (str[j] && str[j] != '$' && str[j] != '\'' && str[j] != '\"')
			j++;
		if (j == i && str[j] && (str[j] != '\'' || str[j] != '\"'))
			j++;
		test = ft_substr(str, i, j - i);
		val = update_expansion(data, val, &test);
		i = j;
	}
	free(str);
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
	if (flag)
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
		while (str[i + ++j] && str[i + j] != '\'' && str[i + j] != '\"')
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
void	parser(t_data	*data)
{
	int		i;

	i = -1;
	while (data->tokens[++i])
	{
		if (data->tokens[i][0] == '\'' || data->tokens[i][0] == '\"'
			|| char_finder(data->tokens[i], '\'', 1)
			|| char_finder(data->tokens[i], '\"', 1))
			data->tokens[i] = quote_str(data, data->tokens[i]);
		else if (data->tokens[i][0] == '$'
			|| char_finder(data->tokens[i], '$', 1))
			data->tokens[i] = expansion(data, data->tokens[i]);
		else if (data->tokens[i][0] == '*'
			|| char_finder(data->tokens[i], '*', 1))
			fix_tokens_wc(data, &i);
	}
	/* for (int i = 0; data->tokens[i]; i++)
		printf("Token %i: :%s:\n", i, data->tokens[i]); */
}
