/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logical_operators.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 18:34:49 by gacorrei          #+#    #+#             */
/*   Updated: 2023/06/03 20:20:23 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_and_or(t_data *data, char *str)
{
	int	i;
	int	flag;
	
	if (str[0] == ')' && data->logic_operator)
	{
		data->logic_operator = 0;
		return (1);
	}
	else if (str[0] == ')' && !data->logic_operator)
		return (0);
	if (str[0] == '(')
	{
		i = -1;
		flag = 0;
		while (str[++i])
		{
			if (delim(&str[i]))
				flag = 1;
			if (str[i])
		}
	}
}
