/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 10:57:25 by gacorrei          #+#    #+#             */
/*   Updated: 2023/06/19 16:45:32 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Changes ctrl+c (SIGINT) so that a new line is correctly displayed.*/
void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_exit_val = 130;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		if (g_exit_val == 130)
			rl_redisplay();
	}
}

/*Runs at start of minishell to capture ctrl+c and ctrl+\ signals.*/
void	signal_global(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}
