/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 10:57:25 by gacorrei          #+#    #+#             */
/*   Updated: 2023/06/22 16:41:57 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Runs at start of missing input to ignore ctrl+c and ctrl+\ signals.*/
void	signal_input(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

/*Changes ctrl+c (SIGINT) so that a new line is correctly displayed.
Special case for child processes to not redisplay prompt.*/
void	signal_cmd_handler(int sig)
{
	if (sig == SIGINT)
	{
		set_exit_code(CTRL_C);
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
	}
	if (sig == SIGQUIT)
	{
		set_exit_code(CTRL_BS);
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
		set_exit_code(130);
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
