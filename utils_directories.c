/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_directories.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 11:16:32 by gacorrei          #+#    #+#             */
/*   Updated: 2023/06/06 12:48:55 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*search_dir(char *pre, char *post)
{
	char			*final_dir;
	DIR				*current;
	struct dirent	*curr;
	int				flag_pre;
	int				flag_post;

	flag_pre = 0;
	flag_post = 0;
	current = opendir(".");
	if (!current)
	{
		printf("Could not open directory.\n");
		return (0);
	}
	curr = readdir(current);
	while (curr)
	{
		if (pre && !ft_strncmp(curr->d_name, pre, ft_strlen(pre)))
			flag_pre = 1;
		if (post && !ft_strncmp(curr->d_name, post, ft_strlen(post)))
			flag_post = 1;
		if ((pre && post && flag_pre && flag_post)
			|| (!pre && post && !flag_pre && flag_post)
			|| (pre && !post && flag_pre && !flag_post))
			break ;
		curr = readdir(current);
		flag_pre = 0;
		flag_post = 0;
	}
	/*STUCK HERE*/
	final_dir = 0;
	closedir(current);
	return (final_dir);
}

char	*test_wildcard(char *token, int wildcard)
{
	char			*dir_pre;
	char			*dir_post;
	char			*final_dir;

	/*TEST THIS CASE, SHOULD ERROR WITH TOO MANY ARGS*/
	if (token[0] == '*' && !token[1])
		return (token);
	dir_pre = ft_substr(token, 0, wildcard);
	if (!dir_pre[0])
	{
		free(dir_pre);
		dir_pre = 0;
	}
	dir_post = ft_substr(token, wildcard + 1, ft_strlen(token) - wildcard - 1);
	if (!dir_post[0])
	{
		free(dir_post);
		dir_post = 0;
	}
	final_dir = search_dir(dir_pre, dir_post);
	return (final_dir);
}

char	*get_dir(t_data *data, char *dir)
{
	t_ll	*temp;
	int		len;

	temp = data->env;
	while (temp)
	{
		len = len_compare(temp->var, dir);
		if (!ft_strncmp(temp->var, dir, len))
			return (temp->value);
		temp = temp->next;
	}
	return (0);
}

void	update_env_dir(t_data *data, char *dir, char *new_dir)
{
	t_ll	*temp;
	int		len;

	temp = data->env;
	while (temp)
	{
		len = len_compare(temp->var, dir);
		if (!ft_strncmp(temp->var, dir, len))
		{
			free(temp->value);
			temp->value = ft_strdup(new_dir);
			break ;
		}
		temp = temp->next;
	}
	return ;
}
