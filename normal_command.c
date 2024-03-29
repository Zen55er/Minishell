/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 11:22:27 by gacorrei          #+#    #+#             */
/*   Updated: 2023/09/14 12:01:41 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Fills 2d array with command name and flags*/
char	**prep_cmds(char **tokens, int token, char *cmd)
{
	char	**cmds;
	int		temp;
	int		i;

	i = 0;
	temp = token - 1;
	while (tokens[++temp])
	{
		if (i && delim_tok(tokens[temp]))
			break ;
		quotes_delimiter_full(tokens, i, 0);
		i++;
	}
	cmds = (char **)malloc(sizeof(char *) * (i + 1));
	cmds[i] = 0;
	i = -1;
	while (token < temp && ++i >= 0)
	{
		if (!i && cmd)
			cmds[i] = cmd;
		else
			cmds[i] = ft_strdup(tokens[token]);
		token++;
	}
	return (cmds);
}

/*Returns cmds struct filled with necessary info for execve*/
t_cmds	*get_cmd(t_data *data, char **tokens, int token)
{
	t_cmds	*cmds;
	char	*cmd;

	cmd = tokens[token];
	if (cmd[0] == '/' && check_path(data->path, cmd))
		cmd = get_end_cmd(cmd);
	cmds = (t_cmds *)malloc(sizeof(t_cmds));
	cmds->cmd = 0;
	if (ft_strcmp(cmd, "awk ") == 0 || ft_strcmp(cmd, "sed ") == 0)
	{
		if (awk_cmd(&cmds, cmd))
			return (cmds);
	}
	else
		cmds->cmd_args = prep_cmds(tokens, token, cmd);
	test_cmd(data, data->path, &cmds);
	return (cmds);
}

/*Copies env to a char ** format for execve*/
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

/*After getting commands and env, calls execve to execute command*/
void	child(t_data *data, char **tokens, int token)
{
	t_cmds	*cmds;
	char	**env2d;

	cmds = get_cmd(data, tokens, token);
	if (!cmds->cmd)
	{
		print_error(cmds->cmd_args[0], 0, "command not found", 0);
		free_child(cmds, 0);
		if (data->permission_flag)
		{
			data->permission_flag = 0;
			free_all(0, data);
			exit (ERROR_EXECUTE_PERMISSIONS);
		}
		free_all(0, data);
		exit (ERROR_WRONG_COMMAND);
	}
	env2d = get_env2d(data->env);
	execve(cmds->cmd, cmds->cmd_args, env2d);
	perror("execve failed.\n");
	free_child(cmds, env2d);
	exit (ERROR_EXIT);
}

/*Prepares cmds struct and sends it to execve*/
int	normal_command(t_data *data, char **tokens, int token)
{
	pid_t	new_fork;
	int		status;

	signal_cmd();
	new_fork = fork();
	if (new_fork < 0)
	{
		perror("Error when forking process");
		return (1);
	}
	else if (new_fork == 0)
		child(data, tokens, token);
	waitpid(new_fork, &status, 0);
	signal_global();
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (WEXITSTATUS(status));
}
