/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 10:57:25 by gacorrei          #+#    #+#             */
/*   Updated: 2023/07/17 13:50:04 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Changes ctrl+c (SIGINT) so that a new line is correctly displayed.
Special case for child processes to not redisplay prompt.*/
void	signal_cmd_handler(int sig)
{
	if (sig == SIGINT)
	{
		update_exit_code(CTRL_C, 1);
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
	}
	if (sig == SIGQUIT)
	{
		update_exit_code(CTRL_BS, 1);
		printf("Quit (core dumped)\n");
	}
}

/*Runs on child processes.*/
void	signal_cmd(void)
{
	signal(SIGINT, signal_cmd_handler);
	signal(SIGQUIT, signal_cmd_handler);
}

/*Changes ctrl+c (SIGINT) so that a new line is correctly displayed.*/
void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		update_exit_code(CTRL_C, 1);
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

/*Runs at start of minishell to capture ctrl+c and ctrl+\ signals.*/
void	signal_global(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}
