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

/*Sets ranks to 0*/
void	rank_reset(t_ll *env)
{
	t_ll	*temp;

	temp = env;
	while (temp)
	{
		temp->rank = 0;
		temp = temp->next;
	}
}

/*Sets ranks for each entry in env for export function*/
void	env_ranking(t_ll *env)
{
	int		len;
	t_ll	*temp;
	t_ll	*temp2;

	rank_reset(env);
	temp = env;
	while (temp)
	{
		temp2 = env;
		while (temp2)
		{
			if (ft_strlen(temp->var) >= ft_strlen(temp2->var))
				len = ft_strlen(temp->var);
			else
				len = ft_strlen(temp2->var);
			if (ft_strncmp(temp->var, temp2->var, len) > 0)
				temp->rank++;
			temp2 = temp2->next;
		}
		temp = temp->next;
	}
}

/*With no arguments simply prints env alphabetically,
otherwise updates env with new args or new arg values*/
int	cmd_export(t_data *data, char *input)
{
	int		i;
	int		j;
	t_ll	*temp;

	(void) input;
	i = -1;
	j = list_size(data->env);
	env_ranking(data->env);
	while (++i < j)
	{
		temp = data->env;
		while (temp)
		{
			if (temp->rank == i)
			{
				printf("declare -x ");
				printf("%s=", temp->var);
				printf("\"%s\"\n", temp->value);
				break ;
			}
			temp = temp->next;
		}
	}
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
