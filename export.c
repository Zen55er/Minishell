/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 11:40:57 by gacorrei          #+#    #+#             */
/*   Updated: 2023/06/23 13:44:35 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Checks if var is already in env*/
int	check_entry(t_data *data, t_ll *list, int tok, int i)
{
	t_ll	*temp;

	temp = list;
	while (temp)
	{
		if (!i)
			i = ft_strlen(data->tokens[tok]);
		if (!ft_strcmp(temp->var, data->tokens[tok]))
		{
			if (temp->value)
				free(temp->value);
			temp->value = ft_substr(data->tokens[tok], i + 1,
					ft_strlen(data->tokens[tok]) - i);
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
int	export_arg(t_data *data, char **tokens, int tok)
{
	int	i;

	if (!tokens[tok + 1] || delim(tokens[tok + 1]))
		return (0);
	while (tokens[++tok])
	{
		if (delim(tokens[tok]))
			break ;
		if (!ft_isalpha(tokens[tok][0]) && tokens[tok][0] != '_')
		{
			printf("export: '%c': not a valid identifier\n",
				tokens[tok][0]);
			return (ERROR_EXIT);
		}
		i = char_finder(tokens[tok], '=');
		if ((tokens[tok][0] == '_' && !tokens[tok][1])
			|| check_entry(data, data->env, tok, i)
			|| check_entry(data, data->exp, tok, i))
			continue ;
		add_to_exp(data, tok, i);
	}
	return (OK_EXIT);
}

/*With no arguments simply prints env alphabetically,
otherwise updates env with new args or new arg values*/
int	cmd_export(t_data *data, char **tokens, int token)
{
	if (export_arg(data, tokens, token))
		return (ERROR_EXIT);
	list_ranking(data->env);
	list_ranking(data->exp);
	print_ordered(data->env);
	print_ordered(data->exp);
	return (OK_EXIT);
}
