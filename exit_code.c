/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_code.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 08:43:01 by gacorrei          #+#    #+#             */
/*   Updated: 2023/07/05 15:51:33 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Formats and prints error message to STDERR.*/
int	print_error(char *source, char *culprit, char *error)
{
	char	*temp1;
	char	*temp2;

	temp1 = ft_strjoin("minishell: ", source);
	temp2 = ft_strjoin(temp1, ": `");
	free(temp1);
	temp1 = ft_strjoin(culprit, "': ");
	temp1 = ft_strjoin_free(temp2, temp1);
	temp2 = ft_strjoin(error, "\n");
	temp1 = ft_strjoin_free(temp1, temp2);
	ft_putstr_fd(temp1, STDERR_FILENO);
	free(temp1);
	return (1);
}

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
