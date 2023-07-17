/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 09:27:09 by gacorrei          #+#    #+#             */
/*   Updated: 2023/07/17 15:06:34 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Frees selected node's memory and connects previous node to next*/
int	unset_var(t_ll **list, int count)
{
	t_ll	*temp;
	t_ll	*temp2;

	if (list_size(*list) == 1)
	{
		free((*list)->var);
		free((*list)->value);
		free(*list);
		*list = 0;
		return (1);
	}
	temp = *list;
	temp2 = *list;
	while (--count > 0)
	{
		temp = temp->next;
		temp2 = temp2->next;
	}
	temp2 = temp2->next;
	temp->next = temp->next->next;
	temp2->next = 0;
	free(temp2->var);
	free(temp2->value);
	free(temp2);
	return (1);
}

/*Checks each node of list until it finds one which has a matching variable
before calling unset_var*/
int	check_unset(t_data *data, t_ll **list, int token, int *i)
{
	t_ll	*temp;
	int		count;

	if (!(*list))
		return (0);
	temp = *list;
	count = 0;
	if (data->tokens[token][ft_strlen(data->tokens[token]) - 1] == '=')
	{
		*i = 1;
		return (print_error("unset", data->tokens[token]
				, "not a valid identifier", 1));
	}
	while (temp)
	{
		if (!ft_strcmp(data->tokens[token], temp->var))
			return (unset_var(list, count));
		temp = temp->next;
		count++;
	}
	return (0);
}

/*Checks if var is valid for unset.*/
int	validate_var_unset(char **tokens, int tok)
{
	int	i;

	if ((!tokens[tok] || !tokens[tok][0]))
		return (print_error("unset", "`'", "not a valid identifier", 0));
	i = -1;
	while (tokens[tok][++i])
	{
		if (i && tokens[tok][i] == '=')
			break ;
		if ((!i && !ft_isalpha(tokens[tok][i]) && tokens[tok][i] != '_')
		|| (i && !ft_isalnum(tokens[tok][i]) && tokens[tok][i] != '_'
		&& tokens[tok][i] != '/' && tokens[tok][i] != ':'))
			return (print_error("unset", tokens[tok]
					, "not a valid identifier", 1));
	}
	return (0);
}

/*If given an argument, checks if it is a variable in env and deletes node*/
int	cmd_unset(t_data *data, char **tokens, int tok)
{
	int	i;

	i = 0;
	if (!tokens[tok + 1] || delim_tok(tokens[tok + 1]))
		return (OK_EXIT);
	while (tokens[++tok])
	{
		if (delim_tok(tokens[tok]))
			break ;
		quotes_delimiter_full(tokens, tok);
		if (validate_var_unset(tokens, tok))
		{
			i = 1;
			continue ;
		}
		if ((tokens[tok][0] == '_' && !tokens[tok][1])
			|| check_unset(data, &data->env, tok, &i))
			continue ;
	}
	if (i)
		return (ERROR_EXIT);
	return (OK_EXIT);
}
