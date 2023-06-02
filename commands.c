/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 10:25:04 by gacorrei          #+#    #+#             */
/*   Updated: 2023/06/02 13:02:34 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Prints arguments of echo, if -n flag is present, does not write newline*/
int	cmd_echo(t_data *data, int tok)
{
	int	n_flag;
	int	i;

	n_flag = 0;
	i = 0;
	if (!data->tokens[tok + 1] || delim(data->tokens[tok + 1]))
		return (ECHO_NO_PRINT);
	while (data->tokens[++tok] && ++i)
	{
		if (delim(data->tokens[tok]))
			break ;
		if (i == 1 && !ft_strncmp(data->tokens[tok], "-n", 2)
			&& !data->tokens[tok][2])
		{
			n_flag = 1;
			continue ;
		}
		if (data->tokens[tok])
			printf("%s", data->tokens[tok]);
		if (data->tokens[tok + 1] && !delim(data->tokens[tok + 1]))
			printf(" ");
	}
	if (!n_flag)
		printf("\n");
	return (OK_EXIT);
}

/*Prints env linked list and any exported variables at the end,
in the same order they were created*/
int	cmd_env(t_data *data)
{
	t_ll	*temp;

	temp = data->env;
	while (temp)
	{
		printf("%s=", temp->var);
		printf("%s\n", temp->value);
		temp = temp->next;
	}
	temp = data->exp;
	while (temp)
	{
		if (!temp->value)
		{
			temp = temp->next;
			continue ;
		}
		printf("%s=", temp->var);
		printf("%s\n", temp->value);
		temp = temp->next;
	}
	return (OK_EXIT);
}

/*Prints "exit", updates prompt, frees memory and exits program*/
void	cmd_exit(t_data *data)
{
	printf("exit\n");
	rl_clear_history();
	free_all(0, data);
	exit (OK_EXIT);
}
