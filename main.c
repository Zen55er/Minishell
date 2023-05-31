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

/*Duplicates envp into a linked list and splits PATH into a 2d array,
adding / to the end*/
void	prep_env_path(t_data *data, char **envp)
{
	int		i;
	int		flag;
	char	*temp;

	i = -1;
	flag = 0;
	while (envp[++i])
	{
		node_add_back(&data->env, new_node(envp[i], 1));
		if (!flag && !ft_strncmp(envp[i], "PATH", 4))
		{
			data->path = ft_split(envp[i] + 5, ':');
			flag = 1;
		}
	}
	i = -1;
	while (data->path[++i])
	{
		temp = data->path[i];
		data->path[i] = ft_strjoin(temp, "/");
		free(temp);
	}
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
	data.tokens = 0;
	data.curr_dir = 0;
	signal_global();
	update_curr_prev(&data);
	prep_env_path(&data, envp);
	while (1)
	{
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
			// executer(&data);
			free_double(data.tokens);
		}
		data.tokens = 0;
	}
	rl_clear_history();
	free_all(0, &data);
	return (0);
}
