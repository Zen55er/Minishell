/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 11:40:57 by gacorrei          #+#    #+#             */
/*   Updated: 2023/07/17 17:07:19 by gacorrei         ###   ########.fr       */
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
		if (!ft_strncmp(temp->var, data->tokens[tok], i))
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

/*Adds node to env list taking into account if there is a value for var*/
void	add_to_env(t_data *data, int tok, int i)
{
	if (check_entry(data, data->env, tok, i))
		return ;
	if (i && data->tokens[tok][i - 1] != '='
		&& !ft_isspace(data->tokens[tok][i - 1])
		&& data->tokens[tok][i + 1] != '='
		&& !ft_isspace(data->tokens[tok][i + 1]))
		node_add_back(&data->env, new_node(data->tokens[tok], 1));
	else
		node_add_back(&data->env, new_node(data->tokens[tok], 0));
}

/*Checks if var is valid*/
int	validate_var(char **tokens, int tok)
{
	int	i;

	if ((!tokens[tok] || !tokens[tok][0]))
		return (print_error("export", "`'", "not a valid identifier", 0));
	i = -1;
	while (tokens[tok][++i])
	{
		if (i && tokens[tok][i] == '=')
			break ;
		if ((!i && !ft_isalpha(tokens[tok][i]) && tokens[tok][i] != '_')
		|| (i && !ft_isalnum(tokens[tok][i]) && tokens[tok][i] != '_'))
			return (print_error("export", tokens[tok]
					, "not a valid identifier", 1));
	}
	return (0);
}

/*Checks for argument formatting and updates env*/
int	export_arg(t_data *data, char **tokens, int tok)
{
	int	i;
	int	f;

	f = 0;
	if (!tokens[tok + 1] || delim_tok(tokens[tok + 1]))
		return (OK_EXIT);
	while (tokens[++tok])
	{
		if (delim_tok(tokens[tok]))
			break ;
		quotes_delimiter_full(tokens, tok, 0);
		if (validate_var(tokens, tok))
		{
			f = 1;
			continue ;
		}
		i = char_finder(tokens[tok], '=');
		if ((tokens[tok][0] == '_' && !tokens[tok][1]))
			continue ;
		add_to_env(data, tok, i);
		quotes_delimiter_full(tokens, tok, 1);
	}
	if (f)
		return (ERROR_EXIT);
	return (OK_EXIT);
}

/*With no arguments simply prints env alphabetically,
otherwise updates env with new args or new arg values*/
int	cmd_export(t_data *data, char **tokens, int token)
{
	if (export_arg(data, tokens, token))
		return (ERROR_EXIT);
	list_ranking(data->env);
	if (tokens[token + 1] && !delim_tok(tokens[token + 1]))
		return (OK_EXIT);
	print_ordered(data->env);
	return (OK_EXIT);
}
