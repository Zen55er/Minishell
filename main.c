/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 14:25:04 by gacorrei          #+#    #+#             */
/*   Updated: 2023/05/24 09:12:24 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Duplicates envp into a linked list and splits PATH into a 2d array*/
void	prep_env_path(t_data *data, char **envp)
{
	int	i;
	int	flag;

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
	/*DELETE AFTER TESTING*/
	/* printf("\nPATH\n");
	i = -1;
	while (data->path[++i])
		printf("%s\n", data->path[i]); */
	return ;
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;
	char	*input;

	(void) ac;
	(void) av;
	data.env = 0;
	data.exp = 0;
	data.tokens = 0;
	signal_global();
	prep_env_path(&data, envp);
	while (1)
	{
		input = readline("minishell> ");
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
		free_all(input, 0);
		if (data.tokens)
		{
			parser(&data);
			free_double(data.tokens);
		}
		data.tokens = 0;
	}
	rl_clear_history();
	free_all(0, &data);
	return (0);
}
