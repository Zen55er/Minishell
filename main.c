/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 14:25:04 by gacorrei          #+#    #+#             */
/*   Updated: 2023/05/22 15:00:28 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Duplicates envp into a linked list and splits PATH into a 2d array*/
void	prep_env_path(t_data *data, char **envp)
{
	int		i;

	i = -1;
	while (envp[++i])
	{
		node_add_back(&data->env, new_node(ft_strdup(envp[i])));
		if (!ft_strncmp(envp[i], "PATH", 4))
			data->path = ft_split(envp[i] + 5, ':');
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
	char	*input2;

	(void) ac;
	(void) av;
	data.env = 0;
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
		input2 = ft_strtrim(input, " ");
		add_history(input2);
		data.tokens = lexer(input);
		free_all(input, input2, 0);
		if (data.tokens)
		{
			parser(&data);
			free_double(data.tokens);
		}
		data.tokens = 0;
	}
	rl_clear_history();
	free_all(0, 0, &data);
	return (0);
}
