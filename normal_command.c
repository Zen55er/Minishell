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

/*Checks if the given command is in PATH*/
int	check_path(char **paths, char *cmd)
{
	int	i;

	i = -1;
	while (paths[++i])
	{
		if (ft_strncmp(paths[i], cmd, ft_strlen(paths[i])) == 0)
			return (1);
	}
	return (0);
}

/*Finds matching quote for awk cases*/
int	awk_quotes(char *cmd, char c, int *i)
{
	int	len;

	*i += 1;
	len = ft_strlen(cmd + 1);
	if (cmd[len] == c)
		return (len - 1);
	return (0);
}

/*Special case for awk calls.*/
int	awk_cmd(t_cmds **cmds, char *cmd)
{
	int	i;
	int	j;

	i = 3;
	j = 0;
	while (cmd[i] == ' ')
		i++;
	if (cmd[i] == 34 || cmd[i] == 39)
		j = awk_quotes(&cmd[i], cmd[i], &i);
	if (j == 0)
		return (1);
	(*cmds)->cmd_args = (char **)malloc(sizeof(char *) * 3);
	(*cmds)->cmd_args[0] = ft_substr(cmd, 0, 3);
	if (j)
		(*cmds)->cmd_args[1] = ft_substr(&cmd[i], 0, j);
	else
		(*cmds)->cmd_args[1] = ft_strdup(&cmd[i]);
	(*cmds)->cmd_args[2] = 0;
	return (0);
}

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

/*Tests commands against path*/
void	test_cmd(char **paths, t_cmds **cmds)
{
	int		i;
	char	*test;

	i = -1;
	while (paths[++i])
	{
		test = ft_strjoin(paths[i], (*cmds)->cmd_args[0]);
		if (!access(test, F_OK & X_OK) && !(*cmds)->cmd)
			(*cmds)->cmd = test;
		else
			free(test);
		if ((*cmds)->cmd)
			break ;
	}
	return ;
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

char	*get_full_var(char *var, char *value)
{
	char	*temp1;
	char	*temp2;

	temp1 = ft_strjoin(var, "=");
	temp2 = ft_strjoin(temp1, value);
	free(temp1);
	return (temp2);
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
		ft_printf("Command not found: %s.\n", cmds->cmd_args[0]);
		free_double(cmds->cmd_args);
		free(cmds->cmd);
		free(cmds);
		return ;
	}
	env2d = get_env2d(data->env);
	execve(cmds->cmd, cmds->cmd_args, env2d);
	perror("execve failed.\n");
	free_double(cmds->cmd_args);
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
