/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 09:39:46 by gacorrei          #+#    #+#             */
/*   Updated: 2023/05/26 10:07:39 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirection(t_data *data)
{
	(void) data;
	return ;
}

void	dollar(t_data *data)
{
	(void) data;
	return ;
}

int	command_check(t_data *data, char *input, int token)
{
	if (!ft_strncmp(input, "echo", ft_strlen(input)))
		return (cmd_echo(data, token));
	if (!ft_strncmp(input, "cd", ft_strlen(input)))
		return (cmd_cd(data, token));
	if (!ft_strncmp(input, "pwd", ft_strlen(input)))
		return (cmd_pwd());
	if (!ft_strncmp(input, "export", ft_strlen(input)))
		return (cmd_export(data, token));
	if (!ft_strncmp(input, "unset", ft_strlen(input)))
		return (cmd_unset(data, token));
	if (!ft_strncmp(input, "env", ft_strlen(input)))
		return (cmd_env(data));
	if (!ft_strncmp(input, "exit", ft_strlen(input)))
		cmd_exit(data);
	return (0);
}

void	parser(t_data *data)
{
	int	i;

	i = -1;
	while (data->tokens[++i])
	{
		if (!ft_strncmp(data->tokens[i], "<", ft_strlen(data->tokens[i])))
			redirection(data);
		else if (!ft_strncmp(data->tokens[i], "$", ft_strlen(data->tokens[i])))
			dollar(data);
		command_check(data, data->tokens[i], i);
		/*SEPARATE COMMAND_CHECK TO RETURN 1 IF IT'S ANY OF THE COMMANDS TO REPLICATE
		AND 0 IF NOT, SO THAT OTHER COMMANDS CAN BE EXECUTED*/
	}
	return ;
}
