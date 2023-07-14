/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 11:51:25 by mpatrao           #+#    #+#             */
/*   Updated: 2023/07/13 11:25:17 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_redir(t_data *data, int c)
{
	if (!ft_strcmp(data->tokens[c], ">") || !ft_strcmp(data->tokens[c], "<")
		|| !ft_strcmp(data->tokens[c], ">>")
		|| !ft_strcmp(data->tokens[c], "<<"))
		return (1);
	return (0);
}

t_cmd_st	*add_cmd_st(char **cmd, int fdin, int fdout)
{
	t_cmd_st	*new;

	new = (t_cmd_st *)malloc(sizeof(t_cmd_st));
	if (!new)
	{
		free_double(&cmd);
		return (0);
	}
	new->next = NULL;
	new->prev = NULL;
	new->cmd = cmd;
	new->redir_in = fdin;
	new->redir_out = fdout;
	return (new);
}

void	data_cmd_st_add_back(t_cmd_st **lst, t_cmd_st *node)
{
	t_cmd_st	*tmp;

	tmp = *lst;
	if (*lst == NULL)
	{
		*lst = node;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
	node->prev = tmp;
}

t_cmd_st	*init_cmd_st_node(t_data *data, int j, int d)
{
	int			c;
	char		**cmd;
	int			fdin;
	int			fdout;

	fdin = STDIN_FILENO;
	fdout = STDOUT_FILENO;
	cmd = ft_calloc(count_args(data, j) + 1, sizeof(char *));
	if (!cmd)
		return (NULL);
	c = j - 1;
	if (get_fds(data->tokens, &fdin, &fdout, c + 1) && int_free(cmd, 1))
		return (NULL);
	while (data->tokens[++c] && ft_strcmp(data->tokens[c], "|"))
	{
		while (data->tokens[c] && check_redir(data, c))
			c = c + 2;
		if (!data->tokens[c] || !ft_strcmp(data->tokens[c], "|"))
			break ;
		if (data->tokens[c])
			cmd[++d] = ft_strdup(data->tokens[c]);
	}
	return (add_cmd_st(cmd, fdin, fdout));
}

int	redirection(t_data *data)
{
	t_cmd_st	*node;
	int			i;
	int			j;

	i = 0;
	j = 0;
	while (data->tokens[i])
	{
		if (!ft_strcmp(data->tokens[i], "|") || !data->tokens[i + 1])
		{
			node = init_cmd_st_node(data, j, -1);
			if (!node)
				return (1);
			data_cmd_st_add_back(&data->cmd_st, node);
			j = i + 1;
		}
		i++;
	}
	return (0);
}
