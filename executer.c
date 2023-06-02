/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatrao <mpatrao@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 09:08:32 by gacorrei          #+#    #+#             */
/*   Updated: 2023/06/02 16:29:21 by mpatrao          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Calls function to execute according to input*/
int	command_call(t_data *data, int token, int command)
{
	if (command == CMD_ECHO)
		return (cmd_echo(data, token));
	if (command == CMD_CD)
		return (cmd_cd(data, token));
	if (command == CMD_PWD)
		return (cmd_pwd(data));
	if (command == CMD_EXPORT)
		return (cmd_export(data, token));
	if (command == CMD_UNSET)
		return (cmd_unset(data, token));
	if (command == CMD_ENV)
		return (cmd_env(data));
	if (command == CMD_EXIT)
		cmd_exit(data);
	normal_command(data, token);
	return (0);
}

/*Checks if input matches specific functions*/
int	command_check(char *input)
{
	if (!ft_strncmp(input, "echo", ft_strlen(input)))
		return (CMD_ECHO);
	if (!ft_strncmp(input, "cd", ft_strlen(input)))
		return (CMD_CD);
	if (!ft_strncmp(input, "pwd", ft_strlen(input)))
		return (CMD_PWD);
	if (!ft_strncmp(input, "export", ft_strlen(input)))
		return (CMD_EXPORT);
	if (!ft_strncmp(input, "unset", ft_strlen(input)))
		return (CMD_UNSET);
	if (!ft_strncmp(input, "env", ft_strlen(input)))
		return (CMD_ENV);
	if (!ft_strncmp(input, "exit", ft_strlen(input)))
		return (CMD_EXIT);
	return (0);
}

/*Iterates through tokens and executes commands*/
void	executer(t_data *data)
{
	int	i;
	/* int	command; */

	i = 0;
	while (data->tokens[i])
	{
		if (!ft_strncmp(data->tokens[i], "<", ft_strlen(data->tokens[i])))
			redirection(data, i);
		else if (!ft_strncmp(data->tokens[i], "|", ft_strlen(data->tokens[i])))
			pipeline(data, i);
		/*vou ter de alterar este while para ele nao correr o command antes do pipe "|" 
		porque se nao vai correr o mesmo command varias vezes*/
		/* /pipe ja esta a dar para casos simples "cmd1 | cmd2"/ */
		/* else if
		{
			command = command_check(data->tokens[i]);
			command_call(data, i, command);
		} */
		while (data->tokens[++i])
		{
			if (delim(data->tokens[i]))
				break ;
		}
	}
	return ;
}
