/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatrao <mpatrao@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 11:51:33 by mpatrao           #+#    #+#             */
/*   Updated: 2023/06/29 17:05:24 by mpatrao          ###   ########.fr       */
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

int	forking(t_data *data, t_cmd_st *node, int in, int out)
{
	static int	i;

	data->pid[i] = fork();
	printf("pid %d: %d\n", i, data->pid[i]);
	if (data->pid[i] < 0)
		return (1);
	if (data->pid[i] == 0)
		if (child_exec_cmd(data, in, out, node) == 1)
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
		printf("pid %d: %d\n", i, data->pid[i]);
		waitpid(data->pid[i], 0, 0);
	}
}


int	pipeline(t_data *data)
{
	int			pipefd[2];
	int			fd_in;
	int			fd_out;
	t_cmd_st	*tmp;

	tmp = data->cmd_st;
	fd_in = STDIN_FILENO;
	while (tmp)
	{
		if (tmp->next && pipe(pipefd))
			return (1);
		fd_in = check_fd_in(tmp, pipefd, fd_in);
		fd_out = check_fd_out(tmp, pipefd);
		if (forking(data, tmp, fd_in, fd_out))
			return (1);
		if (tmp->next)
			fd_in = pipefd[0];
		if (tmp->next)
			tmp = tmp->next;
		else
			break ;
	}
	waiting(data);
	return (0);
}

