/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 10:02:42 by gacorrei          #+#    #+#             */
/*   Updated: 2023/07/07 09:08:09 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Adds every match to their correct spots in new_tok*/
void	add_list_tokens(char **new_tok, t_ll *matches, int i)
{
	while (matches)
	{
		new_tok[i] = ft_strdup(matches->var);
		i++;
		matches = matches->next;
	}
}

/*Counts old tokens*/
int	old_tokens(t_data *data)
{
	int	i;

	i = -1;
	while (data->tokens[++i])
		continue ;
	return (i);
}

/*Calculates necessary space to allocate for new_tok,
copies old tokens to the new variable, including the expanded wildcard values*/
int	add_tokens(t_data *data, t_ll *matches, int token)
{
	int		i;
	int		j;
	int		n_list;
	char	**new_tok;

	n_list = list_size(matches);
	new_tok = (char **)ft_calloc(sizeof(char *), old_tokens(data) + n_list);
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
	free_double(&(data->tokens));
	data->tokens = new_tok;
	return (n_list - 1);
}

/*Compares wildcard str with current folder content.
Only matches hidden files if input also starts with '.'.*/
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
	while (token[i] && content[j])
	{
		if (token[i] == content[j])
			double_increment(&i, &j);
		else if (token[i] == '*')
			found_wildcard(&i, &j, &prev_wc, &backtrack);
		else if (prev_wc == -1)
			return (0);
		else
			return_to_previous(&i, &j, &prev_wc, &backtrack);
	}
	if (!final_wc_check(i, token))
		return (0);
	return (1);
}

/*Opens current directory for searching and
compares each entry with wildcard token.
Places every match in a list which will be added to new tokens.*/
t_ll	*expand_wildcards(char *token)
{
	DIR				*directory;
	struct dirent	*files;
	t_ll			*matches;

	matches = 0;
	directory = opendir(".");
	if (!directory && printf("Could not open directory.\n"))
		return (0);
	files = readdir(directory);
	while (files)
	{
		if (!(files->d_name[0] == '.' && token[0] != '.')
			&& compare_wc(token, files->d_name))
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
