/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logical_operators.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 18:34:49 by gacorrei          #+#    #+#             */
/*   Updated: 2023/06/04 11:18:18 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	logical_search(t_data *data, char *str)
{
	int	i;
	int	flag;

	i = -1;
	flag = 0;
	while (str[++i])
	{
		if (delim(&str[i], 0))
			flag = 1;
		else if (str[i] == ')')
		{
			flag = 2;
			break ;
		}
	}
	if (flag == 2)
	{
		data->logic_operator = 1;
		return (1);
	}
	else if (flag)
	{
		printf("Found unclosed parenthesis: %s\n", str);
		return (-1);
	}
	return (0);
}

int	check_and_or(t_data *data, char *str)
{
	if (str[0] == ')' && data->logic_operator)
	{
		data->logic_operator = 0;
		return (1);
	}
	else if (str[0] == ')' && !data->logic_operator)
		return (0);
	if (str[0] == '(')
		return (logical_search(data, str));
	return (0);
}
