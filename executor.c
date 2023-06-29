/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatrao <mpatrao@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 09:08:32 by gacorrei          #+#    #+#             */
/*   Updated: 2023/06/29 16:39:05 by mpatrao          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Calls function to execute according to input*/
int	command_call(t_data *data, char **tokens, int tok, int cmd)
{
	if (cmd == CMD_ECHO)
		return (cmd_echo(tokens, tok));
	if (cmd == CMD_CD)
		return (cmd_cd(data, tokens, tok));
	if (cmd == CMD_PWD)
		return (cmd_pwd(data));
	if (cmd == CMD_EXPORT)
		return (cmd_export(data, tokens, tok));
	if (cmd == CMD_UNSET)
		return (cmd_unset(data, tokens, tok));
	if (cmd == CMD_ENV)
		return (cmd_env(data));
	if (cmd == CMD_EXIT)
		return (cmd_exit(data, tokens, tok));
	return (normal_command(data, tokens, tok));
}

/*Checks if input matches specific functions*/
int	command_check(char *input)
{
	if (!ft_strcmp(input, "echo"))
		return (CMD_ECHO);
	if (!ft_strcmp(input, "cd"))
		return (CMD_CD);
	if (!ft_strcmp(input, "pwd"))
		return (CMD_PWD);
	if (!ft_strcmp(input, "export"))
		return (CMD_EXPORT);
	if (!ft_strcmp(input, "unset"))
		return (CMD_UNSET);
	if (!ft_strcmp(input, "env"))
		return (CMD_ENV);
	if (!ft_strcmp(input, "exit"))
		return (CMD_EXIT);
	return (0);
}

int	skip_commands(char **tokens, int i)
{
	while (tokens[++i])
	{
		if (!ft_strcmp(tokens[i], "("))
			while (tokens[i] && ft_strcmp(tokens[i], ")"))
				i++;
		if (delim(tokens[i]))
		{
			if (ft_strcmp(tokens[i], "&&")
				&& ft_strcmp(tokens[i], "||"))
				i++;
			break ;
		}
	}
	return (i);
}

int	check_pipe(char **tokens)
{
	int	i;

	i = -1;
	while (tokens[++i])
		if (!ft_strcmp(tokens[i], "|"))
			return (1);
	return (0);
}

/*Iterates through tokens and executes commands.
flag determines if function is called from main (0) or from subshell (1).*/
void	executor(t_data *data, char **tokens, int flag)
{
	int	i;
	int	command;

	i = 0;
	while (tokens[i])
	{
		if (check_pipe(tokens))
		{
			redirection(data);
			data->nodenmb = st_size(data->cmd_st);
			data->pid = (pid_t *)malloc(sizeof(pid_t) * data->nodenmb);
			pipeline(data);
			free(data->pid);
			return ;
		}
		if (!ft_strcmp(tokens[i], "&&") || !ft_strcmp(tokens[i], "||"))
		{
			if (!logical_choice(tokens, i))
			{
				i = skip_commands(tokens, i);
				continue ;
			}
			i++;
		}
		if (delim(tokens[i]) && ft_strcmp(tokens[i], "&&")
			&& ft_strcmp(tokens[i], "||"))
		{
			if (!ft_strcmp(tokens[i], "("))
				subshell(data, tokens, &i);
			i++;
			continue ;
		}
		command = command_check(tokens[i]);
		set_exit_code(command_call(data, tokens, i, command));
		i = skip_commands(tokens, i);
	}
	if (flag)
	{
		set_exit_code(update_exit_code(0, 0));
		exit (update_exit_code(0, 0));
	}
	else
		return ;
}
