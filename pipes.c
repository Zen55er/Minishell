/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatrao <mpatrao@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 11:51:33 by mpatrao           #+#    #+#             */
/*   Updated: 2023/06/29 15:26:53 by mpatrao          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_exec_cmd(t_data *data, int in, int out)
{
	int	i;

	if (dup2(in, STDIN_FILENO) < 0)
		error_handling();
	if (dup2(out, STDOUT_FILENO) < 0)
		error_handling();
	/* INSERT EXEC */
}

void	forking(t_data *data, int pipefd[2], int in, int out)
{
	static int	i;

	data->pid[i] = fork();
	if (data->pid[i] < 0)
		/* error handling */;
	if (data->pid[i] == 0)
		child_exec_cmd(data, in, out);
	i++;
	return (0);
}

int	pipeline(t_data *data)
{
	int			pipefd[2];
	int			fd_in;
	int			fd_out;
	t_cmd_st	*tmp;

	tmp = data->cmd_st;
	while (tmp)
	{
		if (tmp->next)
			pipe(pipefd);
		fd_in = check_fd_in(tmp, pipefd, STDIN_FILENO);
		fd_out = check_fd_out(tmp, pipefd);
		forking(data, pipefd, fd_in, fd_out);
		if (tmp->prev)
			dup2(pipefd[0], STDIN_FILENO);
		if (tmp->next)
			tmp = tmp->next;
		else
			break ;
	}
	wait_pipes();/*ainda por criar */
	normal_command();
	return (0);
}

