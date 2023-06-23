/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatrao <mpatrao@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 11:51:33 by mpatrao           #+#    #+#             */
/*   Updated: 2023/06/23 15:47:55 by mpatrao          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_fd_in(t_cmd_st *node)
{
	int	i;

	i = 0;
	if (node->redir_in != 0)
		i = node->redir_in;
	return (i);
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
	if (node->prev)
		close(in);
	/* fazer em conjunto cm gabriel deixar para ultimo */
	i = command_check(data->cmd_st->cmd);
	command_call(data, 0);
	
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

int	pipeline(t_data *data)
{
	int			pipefd[2];
	int			fd_in;
	t_cmd_st	*tmp;

	fd_in = STDIN_FILENO;
	tmp = data->cmd_st;
	while (tmp)
	{
		if (tmp->next)
			pipe(pipefd);
		fd_in = check_fd_in(tmp);
		forking(data, pipefd, fd_in, tmp);
		close(pipefd[1]);
		if (tmp->prev)
			close(fd_in);
		if (tmp->next)
			tmp = tmp->next;
		else
			break ;
	}
	wait_pipes();/*ainda por criar */
	normal_command();
	return (0);
}
