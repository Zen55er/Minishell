/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatrao <mpatrao@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 11:51:33 by mpatrao           #+#    #+#             */
/*   Updated: 2023/06/22 15:49:58 by mpatrao          ###   ########.fr       */
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
		fd_in = check_fd_in();
		forking(data, pipefd, fd_in, data->cmd_st);
		close(pipefd[1]);
		if (data->cmd_st->prev)
			close(fd_in);
		if (data->cmd_st->next)
			data->cmd_st = data->cmd_st->next;
		else
			break ;
	}
	wait_pipes();/*ainda por criar */
	normal_command();
	return (0);
}

void	child_exec_cmd(t_data *data, int pipefd[2], int in, t_cmd_st *node)
{
	int	i;

	if (dup2(in, STDIN_FILENO) < 0)
		error_handling();
	close(pipefd[0]);
	if (dup2(pipefd[1], STDOUT_FILENO) < 0)
		error_handling();
	close(pipefd[1]);
	if (data->cmd_st->prev)
		close(in);
	i = command_check(data->cmd_st->cmd);
	command_call(?);
	
}

void	forking(t_data *data, int pipefd[2], int in, t_cmd_st *node)
{
	static int	i;

	data->pid[i] = fork();
	if (data->pid[i] < 0)
		/* error handling */;
	if (data->pid[i] == 0)
		child_exec_cmd(data, pipefd, in, node);
	i++;
	return (0);
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
