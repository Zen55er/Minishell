/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 14:25:04 by gacorrei          #+#    #+#             */
/*   Updated: 2023/05/31 14:08:55 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Updates path so that any env changes are reflected in this 2d array.
Splits PATH into a 2d array, adding / to the end*/
void	update_path(t_data  *data)
{
	t_ll	*temp;
	char	*temp2;
	int		len;
	int		i;

	if (data->path)
		free_double(data->path);
	data->path = 0;
	temp = data->env;
	while (temp)
	{
		len = len_compare(temp->var, "PATH");
		if (!ft_strncmp(temp->var, "PATH", len))
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
	return ;
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

/*Gets current working directory to display in prompt*/
char	*build_prompt(t_data *data)
{
	char	*prompt;
	char	*temp;

	temp = ft_strjoin("minishell:", data->curr_dir);
	prompt = ft_strjoin(temp, "$ ");
	free(temp);
	return (prompt);
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;
	char	*input;
	char	*prompt;

	(void) ac;
	(void) av;
	data.env = 0;
	data.exp = 0;
	data.path = 0;
	data.tokens = 0;
	data.curr_dir = 0;
	signal_global();
	update_curr_prev(&data);
	prep_env(&data, envp);
	while (1)
	{
		update_path(&data);
		prompt = build_prompt(&data);
		input = readline(prompt);
		free(prompt);
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (!input[0])
		{
			free(input);
			continue ;
		}
		add_history(input);
		data.tokens = lexer(input);
		free(input);
		if (data.tokens)
		{
			parser(&data);
			executer(&data);
			free_double(data.tokens);
		}
		data.tokens = 0;
	}
	rl_clear_history();
	free_all(0, &data);
	return (0);
}
