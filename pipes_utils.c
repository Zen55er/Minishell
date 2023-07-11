/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatrao <mpatrao@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 14:19:52 by mpatrao           #+#    #+#             */
/*   Updated: 2023/07/11 13:27:47 by mpatrao          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_fd_in(t_cmd_st *node, int pipefd[2], int j)
{
	if (node->redir_in > 0)
	{
		if (j > 0)
			close(j);
		j = node->redir_in;
		close(pipefd[0]);
	}
	return (j);
}

int	check_fd_out(t_cmd_st *node, int pipefd[2])
{
	int	i;

	i = 1;
	if (pipefd[1] > 0)
	{
		i = pipefd[1];
	}
	if (!node->next)
		i = 1;
	if (node->redir_out > 1)
	{
		i = node->redir_out;
		close(pipefd[1]);
	}
	return (i);
}

int	st_size(t_cmd_st *list)
{
	int	n;

	if (!list)
		return (0);
	n = 0;
	while (list)
	{
		list = list->next;
		n++;
	}
	return (n);
}

void	free_cmd_st(t_data *data)
{
	t_cmd_st	*tmp;

	while (data->cmd_st)
	{
		tmp = data->cmd_st;
		data->cmd_st = data->cmd_st->next;
		free_double(&tmp->cmd);
		free(tmp);
	}
}

int	check_pipe(char **tokens, t_data *data)
{
	int	i;

	i = -1;
	while (tokens[++i])
	{
		if (!ft_strcmp(tokens[i], "|"))
		{
			redirection(data);
			data->nodenmb = st_size(data->cmd_st);
			data->pid = (pid_t *)malloc(sizeof(pid_t) * data->nodenmb);
			pipeline(data);
			free(data->pid);
			return (1);
		}
	}
	return (0);
}
