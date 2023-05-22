/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 09:39:46 by gacorrei          #+#    #+#             */
/*   Updated: 2023/05/22 15:15:25 by gacorrei         ###   ########.fr       */
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

int	command_check(t_data *data, char *input)
{
	if (!ft_strncmp(input, "echo", ft_strlen(input)))
		return (1);
	if (!ft_strncmp(input, "cd", ft_strlen(input)))
		return (1);
	if (!ft_strncmp(input, "pwd", ft_strlen(input)))
		return (1);
	if (!ft_strncmp(input, "export", ft_strlen(input)))
		return (1);
	if (!ft_strncmp(input, "unset", ft_strlen(input)))
		return (1);
	if (!ft_strncmp(input, "env", ft_strlen(input)))
		return (cmd_env(data));
	if (!ft_strncmp(input, "exit", ft_strlen(input)))
	{
		printf("exit\n");
		rl_clear_history();
		free_all(0, 0, data);
		exit (1);
	}
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
		command_check(data, data->tokens[i]);
	}
	return ;
}
