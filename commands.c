/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 10:25:04 by gacorrei          #+#    #+#             */
/*   Updated: 2023/05/22 16:02:47 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_env(t_data *data)
{
	t_ll	*temp;

	temp = data->env;
	while (temp)
	{
		printf("%s", temp->var);
		printf("=");
		printf("%s\n", temp->value);
		temp = temp->next;
	}
	return (1);
}
