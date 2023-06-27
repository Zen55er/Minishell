/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_code.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 08:43:01 by gacorrei          #+#    #+#             */
/*   Updated: 2023/06/26 08:59:58 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Gets last exit code.
If update flag is true, updates exit_code.*/
int	update_exit_code(int exit_code, int update)
{
	static int	last_exit_code;

	if (update)
		last_exit_code = exit_code;
	return (last_exit_code);
}

/*Checks for cancellation using ctrl+c and calls update_exit_code.*/
void	set_exit_code(int exit_code)
{
	static int	cancelled;

	if (cancelled)
	{
		cancelled = 0;
		return ;
	}
	if (exit_code == CTRL_C || exit_code == CTRL_BS)
		cancelled = 1;
	update_exit_code(exit_code, 1);
}
