/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatrao <mpatrao@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 11:51:25 by mpatrao           #+#    #+#             */
/*   Updated: 2023/06/16 14:58:46 by mpatrao          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd_st	*add_cmd_st(char **cmd, t_data *data, int fdin, int fdout)
{
	t_cmd_st	*new;

	new = (t_cmd_st *)malloc(sizeof(t_cmd_st));
	if (!new)
	{
		free_double(cmd);
		return (0);
	}
	new->next = NULL;
	new->cmd = cmd;
	new->redir_in = fdin;
	new->redir_out = fdout;
	return (new);
}

void	data_cmd_st_add_back(t_cmd_st *lst, t_cmd_st *node)
{
	t_cmd_st	*tmp;

	tmp = lst;
	if (lst == NULL)
	{
		lst = node;
		return ;
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = NULL;
}

t_cmd_st	*init_cmd_st_node(t_data *data, int i, int j)
{
	int			c;
	int			d;
	char		**cmd;
	int			fdin;
	int			fdout;

	fdin = 0;
	fdout = 0;
	cmd = ft_calloc(count_args(data, j) + 1, sizeof(char *));
	if (!cmd)
		return (NULL);
	c = j + 1;
	d = 0;
	get_fds(data->tokens, &fdin, &fdout, c);
	while (data->tokens[c] && !ft_strncmp(data->tokens[c], "|", 2))
	{
		if (!ft_strncmp(data->tokens[c], ">", 2)
			|| !ft_strncmp(data->tokens[c], ">>", 2)
			|| !ft_strncmp(data->tokens[c], "<", 2)
			|| !ft_strncmp(data->tokens[c], "<<", 2))
			c = c + 2;
		if (data->tokens[c])
			cmd[d++] = ft_strdup(data->tokens[c++]);
	}
	return (add_cmd_st(cmd, data, fdin, fdout));
}

int	redirection(t_data *data)
{
	t_cmd_st	*node;
	int			i;
	int			j;

	i = 0;
	j = 0;
	count_pipes(data);
	while (data->tokens[i])
	{
		if (!ft_strncmp(data->tokens[i], "|", 2) || !data->tokens[i + 1])
		{
			node = init_cmd_st_node(data, i, j);
			if (!node)
				return (1);
			data_cmd_st_add_back(data->cmd_st, node);
			j = i;
		}
		i++;
	}
	return (0);
}
