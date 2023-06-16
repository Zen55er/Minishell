/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatrao <mpatrao@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 11:51:33 by mpatrao           #+#    #+#             */
/*   Updated: 2023/06/16 16:00:24 by mpatrao          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipeline(t_data *data, int i)
{
	while (data->cmd_st)
	{
		pipes(data, i);
		dup2(data->lastfdout, STDIN_FILENO);
		if (data->cmd_st->next)
			data->cmd_st = data->cmd_st->next;
	}
	return (0);
}

void	pipes(t_data *data, int i)
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
		command = command_check(data->tokens[i]);
		command_call(data, i, command);
	}
	else
	{
		close(pipefd[1]);
		data->lastfdout = pipefd[0];
	}
}
