/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 17:55:19 by gacorrei          #+#    #+#             */
/*   Updated: 2023/06/26 12:57:53 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_sub_tokens(t_data *data, int token)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (data->tokens[++token])
	{
		if (!smart_compare(data->tokens[token], "("))
			flag++;
		else if (!smart_compare(data->tokens[token], ")"))
		{
			if (flag)
				flag--;
			else
				break ;
		}
		i++;
	}
	return (i);
}

void	assign_sub_tokens(t_data *data, char **sub_tokens, int *token)
{
	int	i;
	int	flag;

	flag = 0;
	i = -1;
	while (data->tokens[++(*token)])
	{
		if (!smart_compare(data->tokens[*token], "("))
			flag++;
		else if (!smart_compare(data->tokens[*token], ")"))
		{
			if (flag)
				flag--;
			else
				break ;
		}
		sub_tokens[++i] = data->tokens[*token];
	}
	return ;
}

/*Copies tokens that are inside parentheses and sends them to executor.*/
void	subshell(t_data *data, int *token)
{
	int		i;
	pid_t	pid;
	int		status;
	char	**sub_tokens;

	i = count_sub_tokens(data, *token);
	sub_tokens = (char **)ft_calloc(sizeof(char *), (i + 1));
	if (!sub_tokens)
		return ;
	assign_sub_tokens(data, sub_tokens, token);
	pid = fork();
	if (pid == -1)
		return ;
	else if (!pid)
		executor(data, sub_tokens, 1);
	waitpid(pid, &status, 0);
	set_exit_code(WEXITSTATUS(status));
	free(sub_tokens);
	return ;
}
