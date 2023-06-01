/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 09:39:46 by gacorrei          #+#    #+#             */
/*   Updated: 2023/05/31 14:37:41 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Joins test to val if it exists after expanding variable
or if it is just text*/
char	*update_expansion(t_data *data, char *val, char **test)
{
	char	*temp;
	char	*temp_val;

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
		while (str[j] && str[j] != '$')
			j++;
		test = ft_substr(str, i, j - i);
		val = update_expansion(data, val, &test);
		i = j;
	}
	printf("Starting str: %s\n", str);
	printf("Expanded str: %s\n", val);
	free(str);
	return (val);
}

/*Returns new string with text formatted according to quote type*/
char	*quotes(t_data *data, char *str)
{
	(void) data;
	(void) str;
	return (0);
}

/*Parses cases with $ and quotes*/
void	parser(t_data	*data)
{
	int	i;

	i = -1;
	while (data->tokens[++i])
	{
		if (data->tokens[i][0] == '\'' || data->tokens[i][0] == '\"')
			data->tokens[i] = quotes(data, data->tokens[i]);
		else
			data->tokens[i] = expansion(data, data->tokens[i]);
	}
}
