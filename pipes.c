/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 11:51:33 by mpatrao           #+#    #+#             */
/*   Updated: 2023/07/17 13:49:14 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	child_exec_cmd(t_data *data, int in, int out, t_cmd_st *nd)
{
	int	p;

	p = -1;
	if (dup2(in, STDIN_FILENO) < 0)
		exit (update_exit_code(1, 1));
	if (dup2(out, STDOUT_FILENO) < 0)
		exit (update_exit_code(1, 1));
	if (data->pipefd[0] > 2)
		close(data->pipefd[0]);
	if (nd->fd_out > 2)
		close(nd->fd_out);
	if (nd->fd_in > 2)
		close(nd->fd_in);
	subshell(data, nd->cmd, &p);
	exit (update_exit_code(0, 0));
}

int	forking(t_data *data, t_cmd_st *node, int flag)
{
	static int	i;

	if (!flag)
	{
		i = 0;
		return (0);
	}
	data->pid[i] = fork();
	if (data->pid[i] < 0)
		return (update_exit_code(1, 1));
	if (data->pid[i] == 0)
		child_exec_cmd(data, data->fd_in, data->fd_out, node);
	if (node->fd_out > 2)
		close(node->fd_out);
	if (node->fd_in > 2)
		close(node->fd_in);
	i++;
	return (0);
}

void	waiting(t_data *data)
{
	int	i;
	int	status;

	i = -1;
	while (++i < st_size(data->cmd_st))
	{
		waitpid(data->pid[i], &status, 0);
		update_exit_code(WEXITSTATUS(status), 1);
	}
}

int	pipeline(t_data *data)
{
	t_cmd_st	*tmp;

	tmp = data->cmd_st;
	data->fd_in = STDIN_FILENO;
	forking(data, tmp, 0);
	while (tmp)
	{
		if (tmp->next && pipe(data->pipefd))
			return (update_exit_code(1, 1));
		data->fd_in = check_fd_in(tmp, data->fd_in);
		data->fd_out = check_fd_out(tmp, data->pipefd);
		tmp->fd_in = data->fd_in;
		tmp->fd_out = data->fd_out;
		if (forking(data, tmp, 1))
			return (update_exit_code(1, 1));
		if (tmp->next)
			data->fd_in = data->pipefd[0];
		if (tmp->next)
			tmp = tmp->next;
		else
			break ;
	}
	waiting(data);
	return (0);
}
