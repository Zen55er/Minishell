/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 14:25:04 by gacorrei          #+#    #+#             */
/*   Updated: 2023/07/17 15:52:39 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Updates path so that any env changes are reflected in this 2d array.
Splits PATH into a 2d array, adding / to the end*/
void	update_path(t_data *data)
{
	t_ll	*temp;
	char	*temp2;
	int		i;

	if (data->path)
		free_double(&(data->path));
	data->path = 0;
	temp = data->env;
	while (temp)
	{
		if (!ft_strcmp(temp->var, "PATH"))
			data->path = ft_split(temp->value, ':');
		temp = temp->next;
	}
	if (!data->path)
		return ;
	i = -1;
	while (data->path[++i])
	{
		temp2 = data->path[i];
		data->path[i] = ft_strjoin(temp2, "/");
		free(temp2);
	}
}

/*Duplicates envp into a linked list and call update_path*/
void	prep_env(t_data *data, char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
		node_add_back(&data->env, new_node(envp[i], 1));
	update_path(data);
	return ;
}

/*Gets current working directory to display in prompt.
Updates PATH in env and reads input from user.*/
char	*get_input(t_data *data)
{
	char	*input;
	char	*prompt;
	char	*temp;

	update_path(data);
	temp = ft_strjoin("minishell:", data->curr_dir);
	prompt = ft_strjoin(temp, "$ ");
	free(temp);
	input = readline(prompt);
	free(prompt);
	return (input);
}

/*Initializes data variables, starts signal interception, env copy and
current and previous directories*/
void	init(t_data *data, char **envp)
{
	data->env = 0;
	data->path = 0;
	data->tokens = 0;
	data->curr_dir = 0;
	data->logic_operator = 0;
	data->cmd_st = 0;
	data->permission_flag = 0;
	data->pipefd[0] = -1;
	data->pipefd[1] = -1;
	data->quote_flag = 0;
	signal_global();
	prep_env(data, envp);
	update_curr_prev(data);
	unlink(".here_doc");
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;
	char	*input;

	(void) ac;
	(void) av;
	init(&data, envp);
	while (1)
	{
		input = get_input(&data);
		if (!input && printf("exit\n"))
			break ;
		if (!input[0])
		{
			free(input);
			continue ;
		}
		add_history(input);
		if (!lexer(&data, &input))
			if (!parser(&data))
				executor(&data, data.tokens, 0);
	}
	free_all(0, &data);
	return (update_exit_code(0, 0));
}
