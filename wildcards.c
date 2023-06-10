/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 10:02:42 by gacorrei          #+#    #+#             */
/*   Updated: 2023/06/10 08:57:07 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_list_tokens(char **new_tok, t_ll *matches, int i)
{
	t_ll	*temp;
	/*TEST WITHOUT TEMP*/

	temp = matches;
	while (temp)
	{
		new_tok[i] = ft_strdup(temp->var);
		i++;
		temp = temp->next;
	}
}

int	add_tokens(t_data *data, t_ll *matches, int token)
{
	int		i;
	int		j;
	int		n_tok;
	int		n_list;
	char	**new_tok;

	n_tok = 0;
	while (data->tokens[n_tok])
		n_tok++;
	n_list = list_size(matches);
	new_tok = (char **)malloc(sizeof(char *) * (n_tok + n_list));
	i = -1;
	j = 0;
	while (data->tokens[++i])
	{
		if (i == token)
		{
			add_list_tokens(new_tok, matches, i);
			j = n_list - 1;
			i++;
		}
		if (!data->tokens[i])
			break ;
		new_tok[i + j] = ft_strdup(data->tokens[i]);
	}
	new_tok[i + j] = 0;
	free_double(data->tokens);
	data->tokens = new_tok;
	return (n_list - 1);
}

int	compare_wc(char *token, char *content)
{
	int	i;
	int	j;
	int	prev_wc;
	int	backtrack;

	i = 0;
	j = 0;
	prev_wc = -1;
	backtrack = -1;
	if ((content[0] == '.' && token[0] != '.'))
		return (0);
	while (token[i] && content[j])
	{
		if (token[i] == content[j])
		{
			i++;
			j++;
		}
		else if (token[i] == '*')
		{
			i++;
			prev_wc = i;
			backtrack = j;
		}
		else if (prev_wc == -1)
			return (0);
		else
		{
			i = prev_wc;
			j = backtrack++;
		}
	}
	while (token[i])
	{
		if (token[i] != '*')
			return (0);
		i++;
	}
	return (1);
}

t_ll	*expand_wildcards(char *token)
{
	DIR				*directory;
	struct dirent	*files;
	t_ll			*matches;

	matches = 0;
	directory = opendir(".");
	if (!directory)
	{
		printf("Could not open directory.\n");
		return (0);
	}
	files = readdir(directory);
	while (files)
	{
		if (compare_wc(token, files->d_name))
		{
			if (!matches)
				matches = new_node(files->d_name, 0);
			else
				node_add_back(&matches, new_node(files->d_name, 0));
		}
		files = readdir(directory);
	}
	closedir(directory);
	list_ranking(matches);
	return (matches);
}
