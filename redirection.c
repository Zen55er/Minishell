/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatrao <mpatrao@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 11:51:25 by mpatrao           #+#    #+#             */
/*   Updated: 2023/06/09 19:09:16 by mpatrao          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



void	count_pipes(t_data *data)
{
	(void)data;
	/* int	i;

	i = 0;
	data->cmd_st->num_pipes = 0;
	while (data->tokens[i])
	{
		if (data->tokens[i] == "|")
			data->cmd_st->num_pipes++;
		i++;
	} */
	return (0);
}

int	count_args(t_data *data)
{
	int	i;

	i = 0;
	while (data->tokens[i] && data->tokens[i] != "|")
		i++;
	return (i);
}

t_cmd_st	*initialize_cmd_st(t_data *data)
{
	int			arg_size;
	char		**cmd;

	count_pipes(data);
	arg_size = count_args(data);
	cmd = ft_calloc(arg_size + 1, sizeof(char *));
	while (arg_size > 0)
	{
		;
	}
}
/* vou ter de calcular a memoria(count args) para alocar um double array
com o tamanho correcto para conter todos os comandos previos aos pipes */
/* separando lista cmd_st em nodes cada um contendo os commands entre cada pipe
e as redirecçoes respectivas */

int	redirection(t_data *data)
{
	t_cmd_st	*node;

	node = initialize_cmd_st(data);
}
