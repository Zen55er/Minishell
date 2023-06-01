/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 11:22:27 by gacorrei          #+#    #+#             */
/*   Updated: 2023/05/29 16:30:01 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Fills 2d array with command name and flags*/
char	**prep_cmds(t_data *data, int token)
{
	char	**cmds;
	int		temp;
	int		i;

	i = 0;
	temp = token;
	while (data->tokens[temp])
	{
		if (delim(data->tokens[temp]))
			break ;
		i++;
		temp++;
	}
	cmds = (char **)malloc(sizeof(char *) * (i + 1));
	cmds[i] = 0;
	i = 0;
	while (token < temp)
	{
		cmds[i] = ft_strdup(data->tokens[token]);
		token++;
		i++;
	}
	return (cmds);
}

t_cmds	*get_cmd(t_data *data, int token)
{
	t_cmds	*cmds;
	char	*cmd;

	cmd = data->tokens[token];
	if (cmd[0] == '/' && check_path(data->path, cmd))
		cmd = ft_strrchr(data->tokens[token], '/');
	cmds = (t_cmds *)malloc(sizeof(t_cmds));
	cmds->cmd = 0;
	if (ft_strncmp(cmd, "awk ", 4) == 0 || ft_strncmp(cmd, "sed ", 4) == 0)
	{
		if (awk_cmd(&cmds, cmd))
			return (cmds);
	}
	else
		cmds->cmd_args = prep_cmds(data, token);
	test_cmd(data->path, &cmds);
	return (cmds);
}

char	**get_env2d(t_ll *env)
{
	char	**env2d;
	t_ll	*temp;
	int		size;
	int		i;

	size = list_size(env);
	env2d = (char **)malloc(sizeof(char *) * (size + 1));
	temp = env;
	i = -1;
	while (temp)
	{
		env2d[++i] = get_full_var(temp->var, temp->value);
		temp = temp->next;
	}
	env2d[++i] = 0;
	return (env2d);
}

void	child(t_data *data, int token)
{
	t_cmds	*cmds;
	char	**env2d;

	cmds = get_cmd(data, token);
	if (!cmds->cmd)
	{
		ft_printf("Command not found: %s\n", cmds->cmd_args[0]);
		free_double(cmds->cmd_args);
		free(cmds->cmd);
		free(cmds);
		return ;
	}
	env2d = get_env2d(data->env);
	execve(cmds->cmd, cmds->cmd_args, env2d);
	perror("execve failed.\n");
	free_double(cmds->cmd_args);
	free_double(env2d);
	free(cmds->cmd);
	free(cmds);
	return ;
}

/*Prepares cmds struct and sends it to execve*/
int	normal_command(t_data *data, int token)
{
	pid_t		new_fork;

	new_fork = fork();
	if (new_fork < 0)
		perror("Error when forking process");
	else if (new_fork == 0)
		child(data, token);
	waitpid(new_fork, 0, 0);
	return (0);
}
