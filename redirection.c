/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatrao <mpatrao@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 11:51:25 by mpatrao           #+#    #+#             */
/*   Updated: 2023/06/12 17:27:00 by mpatrao          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd_st	*add_cmd_st(char **cmd, t_data *data)
{
	t_cmd_st	*new;

	new = (t_cmd_st *)ft_calloc(sizeof(t_cmd_st));
	if (!new)
		return (0);
	new->next = NULL;
	new->prev = NULL;
	new->cmd = cmd;
	/* on hold até descobrir como organizar os redirs */
}

void	count_pipes(t_data *data)
{
	int	i;

	i = 0;
	data->cmd_st->num_pipes = 0;
	while (data->tokens[i])
	{
		if (data->tokens[i] == "|")
			data->cmd_st->num_pipes++;
		i++;
	}
}

int	count_args(t_data *data, int j)
{
	int	c;

	c = j + 1;
	while (data->tokens[c] && data->tokens[c] != "|")
		c++;
	return (c);
}

/* inicializa um node e aloca todos os commands numa
 matriz até encontrar um pipe ou acabar o cmd array
guarda tambem qualquer redirection que possa ocorrer*/

t_cmd_st	*initialize_cmd_st(t_data *data, int i, int j)
{
	int			arg_size;
	int			c;
	int			d;
	char		**cmd;

	if (!data->tokens[i + 1])
		i++;
	arg_size = count_args(data, j);
	cmd = ft_calloc(arg_size + 1, sizeof(char *));
	c = j + 1;
	d = 0;
	/* tenho de descobrir como vasculhar por redirections
	e guardar o fd para onde devo redirecionar enquanto
	aloco os commands */
	while (arg_size > 0)
	{
		if (data->tokens[c])
			cmd[d++] = ft_strdup(data->tokens[c++]);
		arg_size--;
	}
	return (add_cmd_st(cmd, data));
}

/*vou ter de calcular a memoria(count args)
para alocar um double array
com o tamanho correcto para conter todos os comandos previos aos pipes */
/*separando lista cmd_st em nodes 
cada um contendo os commands entre cada pipe
e as redirecçoes respectivas */

int	redirection(t_data *data)
{
	t_cmd_st	*node;
	int			i;
	int			j;

	i = 0;
	j = 0;
	count_pipes(data);
	while (data->tokens[i])
	{
		if (data->tokens[i] == "|" || !data->tokens[i + 1])
		{
			node = initialize_cmd_st(data, i, j);
			data_cmd_st_add_back(data, node);
			/* vai adicionar a command struct a DATA, data->cmd_st */
			j = i;
		}
		i++;
	}
	return (success?);
}
