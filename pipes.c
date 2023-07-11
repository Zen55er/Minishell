/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatrao <mpatrao@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 11:51:33 by mpatrao           #+#    #+#             */
/*   Updated: 2023/07/11 13:17:26 by mpatrao          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	child_exec_cmd(t_data *data, int in, int out, t_cmd_st *node)
{
	int	p;

	p = -1;
	if (dup2(in, STDIN_FILENO) < 0)
		exit (1);
	if (dup2(out, STDOUT_FILENO) < 0)
		exit (1);
	subshell(data, node->cmd, &p);
	exit (0);
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
		return (1);
	if (data->pid[i] == 0)
		if (child_exec_cmd(data, data->fd_in, data->fd_out, node) == 1)
			return (1);
	i++;
	return (0);
}

void	waiting(t_data *data)
{
	int	i;

	i = -1;
	while (++i < st_size(data->cmd_st))
	{
		waitpid(data->pid[i], 0, 0);
	}
}

int	pipeline(t_data *data)
{
	int			pipefd[2];
	t_cmd_st	*tmp;

	tmp = data->cmd_st;
	data->fd_in = STDIN_FILENO;
	forking(data, tmp, 0);
	while (tmp)
	{
		if (tmp->next && pipe(pipefd))
			return (1);
		data->fd_in = check_fd_in(tmp, pipefd, data->fd_in);
		data->fd_out = check_fd_out(tmp, pipefd);
		if (forking(data, tmp, 1))
			return (1);
		close(pipefd[1]);
		if (tmp->next)
			data->fd_in = pipefd[0];
		if (tmp->next)
			tmp = tmp->next;
		else
			break ;
	}
	waiting(data);
	return (0);
}
