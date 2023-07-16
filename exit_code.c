/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_code.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatrao <mpatrao@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 08:43:01 by gacorrei          #+#    #+#             */
/*   Updated: 2023/07/14 16:55:38 by mpatrao          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Formats str portion of error message. If flag is active, add ` and '*/
char	*format_str(char *str, int flag)
{
	char	*temp1;
	char	*temp2;

	if (flag)
	{
		temp2 = ft_strjoin("`", str);
		if (flag == 1)
			temp1 = ft_strjoin(temp2, "': ");
		else
			temp1 = ft_strjoin(temp2, "'");
		free(temp2);
	}
	else
		temp1 = ft_strjoin(str, ": ");
	return (temp1);
}

/*Formats and prints error message to STDERR.*/
int	print_error(char *src, char *str, char *err, int flag)
{
	char	*temp1;
	char	*temp2;

	if (src && flag != 2)
		temp1 = ft_strjoin(src, ": ");
	else if (src && flag == 2)
		temp1 = ft_strjoin(src, " ");
	else
		temp1 = ft_strdup("");
	temp2 = ft_strjoin("minishell: ", temp1);
	free(temp1);
	if (str)
	{
		temp1 = format_str(str, flag);
		temp2 = ft_strjoin_free(temp2, temp1);
	}
	if (err)
		temp1 = ft_strjoin(err, "\n");
	else
		temp1 = ft_strdup("\n");
	temp1 = ft_strjoin_free(temp2, temp1);
	ft_putstr_fd(temp1, STDERR_FILENO);
	return (int_free(temp1, 1));
}

/*Prints error for heredoc cancellation cases*/
void	print_error2(char *limiter, int *n)
{
	char	*tmp;
	char	*s2;

	tmp = ft_strdup("minishell: warning: here-document at line ");
	s2 = ft_itoa(n);
	tmp = ft_strjoin_free(tmp, s2);
	s2 = ft_strdup(" delimited by end-of-file (wanted `");
	tmp = ft_strjoin_free(tmp, s2);
	s2 = ft_strjoin(limiter, "')\n");
	tmp = ft_strjoin_free(tmp, s2);
	ft_putstr_fd(tmp, 2);
	free(tmp);
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
