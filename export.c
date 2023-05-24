/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 11:40:57 by gacorrei          #+#    #+#             */
/*   Updated: 2023/05/24 12:11:40 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Checks if var is already in env*/
int	check_entry(t_data *data, t_ll *list, int tok, int i)
{
	t_ll	*temp;
	int		len;

	temp = list;
	while (temp)
	{
		if (i >= (int)ft_strlen(temp->var))
			len = (int)ft_strlen(data->tokens[tok]);
		else
			len = (int)ft_strlen(temp->var);
		if (!ft_strncmp(temp->var, data->tokens[tok], len))
		{
			/*HERE!!!*/
			update_var();
			return (1);
		}
		temp = temp->next;
	}
	return (0);
}

/*Adds node to exp list taking into account if there is a value for var*/
void	add_to_exp(t_data *data, int tok, int i)
{
	if (i && data->tokens[tok][i - 1] != '='
		&& !ft_isspace(data->tokens[tok][i - 1])
		&& data->tokens[tok][i + 1] != '='
		&& !ft_isspace(data->tokens[tok][i + 1]))
		node_add_front(&data->exp, new_node(data->tokens[tok], 1));
	else
		node_add_front(&data->exp, new_node(data->tokens[tok], 0));
}

/*Checks for argument formatting and updates exp*/
int	export_arg(t_data *data, int tok)
{
	int	i;

	if (!data->tokens[tok + 1] || delim(data->tokens[tok + 1]))
		return (0);
	while (data->tokens[++tok])
	{
		if (delim(data->tokens[tok]))
			break ;
		if (!ft_isalpha(data->tokens[tok][0]) && data->tokens[tok][0] != '_')
		{
			printf("export: '%c': not a valid identifier\n",
				data->tokens[tok][0]);
			return (0);
		}
		i = char_finder(data->tokens[tok], '=');
		if ((data->tokens[tok][0] == '_' && !data->tokens[tok][1])
			|| check_entry(data, data->env, tok, i)
			|| check_entry(data, data->exp, tok, i))
			continue ;
		add_to_exp(data, tok, i);
	}
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
	list_ranking(data->env);
	list_ranking(data->exp);
	print_ordered(data->env);
	print_ordered(data->exp);
	return (0);
}
