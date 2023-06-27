/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatrao <mpatrao@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 11:51:33 by mpatrao           #+#    #+#             */
/*   Updated: 2023/06/27 15:22:57 by mpatrao          ###   ########.fr       */
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

int	check_fd_out(t_cmd_st *node)
{
	int	i;

	i = 1;
	if (node->redir_in != 0)
		i = node->redir_out;
	return (i);
}

void	child_exec_cmd(t_data *data, int pipefd[2], int in, int out)
{
	int	i;

	/* default: if first node its stdinput
	if its any in the middle its the previous pipe
	IF THERE ARE ANY REDIRS THOSE ARE THE PRIORITY
	(Still need to implement this logic) */
	if (dup2(in, STDIN_FILENO) < 0)
		error_handling();
	close(pipefd[0]);
	if (dup2(pipefd[1], STDOUT_FILENO) < 0)
		error_handling();
	close(pipefd[1]);
	if (data->cmd_st->prev)
		close(in);
	/* fazer em conjunto cm gabriel deixar para ultimo */
	/* i = command_check(data->cmd_st->cmd);
	command_call(data, 0); */
}

void	forking(t_data *data, int pipefd[2], int in, int out)
{
	static int	i;

	data->pid[i] = fork();
	if (data->pid[i] < 0)
		/* error handling */;
	if (data->pid[i] == 0)
		child_exec_cmd(data, pipefd, in, out);
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
		fd_in = check_fd_in(tmp);
		fd_out = check_fd_out(tmp);
		/*this forking func has to be 
		conditional i think?
		what happens when theres only one node?
		pipefd[] will be full of 0s*/
		/* how do we deal with a single node? ask gabriel*/
		forking(data, pipefd, fd_in, fd_out);
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
