/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatrao <mpatrao@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 11:51:33 by mpatrao           #+#    #+#             */
/*   Updated: 2023/06/20 16:39:59 by mpatrao          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipeline(t_data *data)
{
	int	pipefd[2];
	int	fd_in;

	fd_in = STDIN_FILENO;
	while (data->cmd_st)
	{
		if (data->cmd_st->next)
			pipe(pipefd);
		forking(data, pipefd, fd_in, data->cmd_st);
		close (pipefd[1]);
		fd_in = /* check for heredoc ? */;
		if (data->cmd_st->next)
			data->cmd_st = data->cmd_st->next;
		else
			break ;
	}
	wait_pipes();/* ainda por criar */
	return (0);
}

void	forking(t_data *data, int *fds, int in, t_cmd_st *head)
{
	int	i;
/* prototipo */
	dup2(in, STDIN_FILENO);
	close (fds[0]);
	dup2(fds[1], STDOUT_FILENO);
	close (fds[1]);
	if (exist prev command)
		close (in);
	i = command_call();
	data->last_exit = command_call();
}

/* void	pipes(int fd)
{
	pid_t	pid;
	int		pipefd[2];
	int		command;

	if (pipe(pipefd) == -1)
	{
		perror("Minishell");
		exit(1);
	}
	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
	}
	else
	{
		close(pipefd[1]);
		data->lastfdout = pipefd[0];
	}
} */
