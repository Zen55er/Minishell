/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 11:40:57 by gacorrei          #+#    #+#             */
/*   Updated: 2023/05/24 10:11:48 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

/*Checks for argument formatting and updates exp*/
int	export_arg(t_data *data, int token)
{
	int	i;
	int	j;

	i = ++token;
	if (!data->tokens[i] || delim(data->tokens[i]))
		return (0);
	j = char_finder(data->tokens[token], '=');
	if (j && data->tokens[token][j - 1] != '='
		&& !ft_isspace(data->tokens[token][j - 1])
		&& data->tokens[token][j + 1] != '='
		&& !ft_isspace(data->tokens[token][j + 1]))
		node_add_front(&data->exp, new_node(data->tokens[token], 1));
	else
		node_add_front(&data->exp, new_node(data->tokens[token], 0));
	return (1);
}

/*Prints linked list in alphabetical order*/
void	print_ordered(t_ll *list)
{
	int		i;
	int		j;
	t_ll	*temp;

	i = -1;
	j = list_size(list);
	while (++i < j)
	{
		temp = list;
		while (temp)
		{
			if (temp->rank == i)
			{
				printf("declare -x ");
				printf("%s", temp->var);
				if (temp->value)
					printf("=\"%s\"\n", temp->value);
				else
					printf("\n");
				break ;
			}
			temp = temp->next;
		}
	}
}

/*With no arguments simply prints env alphabetically,
otherwise updates env with new args or new arg values*/
int	cmd_export(t_data *data, int token)
{
	if (export_arg(data, token))
		return (1);
	env_ranking(data->env);
	env_ranking(data->exp);
	print_ordered(data->env);
	print_ordered(data->exp);
	return (0);
}
