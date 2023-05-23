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

int	cmd_echo(t_data *data)
{
	(void) data;
	return (1);
}

int	cmd_cd(t_data *data)
{
	(void) data;
	return (1);
}

int	cmd_pwd(t_data *data)
{
	(void) data;
	return (1);
}

int	cmd_unset(t_data *data)
{
	(void) data;
	return (1);
}

/*Prints env linked list*/
int	cmd_env(t_data *data)
{
	t_ll	*temp;

	temp = data->env;
	/*ADD NEW LOGIC FROM EXPORT!!
	PRINT EXP AFTER HOME*/
	while (temp)
	{
		printf("%s=", temp->var);
		printf("%s\n", temp->value);
		temp = temp->next;
	}
	return (1);
}

/*Prints "exit", updates prompt, frees memory and exits program*/
void	cmd_exit(t_data *data)
{
	printf("exit\n");
	rl_clear_history();
	free_all(0, 0, data);
	exit (1);
}
